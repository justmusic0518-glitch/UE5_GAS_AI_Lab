// CombatPlayerCharacter.cpp
#include "CombatPlayerCharacter.h"
#include "Engine/Engine.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GAS_AI_Prototype/AbilitySystem/Attributes/CombatAttributeSet.h"
#include "GAS_AI_Prototype/Character/Input/GAInputConfig.h"
#include "GAS_AI_Prototype/AbilitySystem/Abilities/GAGameplayAbilityBase.h"
#include "GAS_AI_Prototype/AbilitySystem/Abilities/Player/GAPlayerAttack.h"
#include "GAS_AI_Prototype/AbilitySystem/Abilities/Player/GAPlayerDodge.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ACombatPlayerCharacter::ACombatPlayerCharacter(){
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// CharacterMovementComponent.h #include 
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	springArmComponent->SetupAttachment(RootComponent);
	minArmLength = 100.0f;
	maxArmLength = 500.0f;
	springArmComponent->TargetArmLength = maxArmLength;
	springArmComponent->bUsePawnControlRotation = true;
	
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComponent->SetupAttachment(springArmComponent);
	
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	zoomSpeed = 50.0f;
	bIsLockOn = false;
}

void ACombatPlayerCharacter::BeginPlay(){
	Super::BeginPlay();
		
	abilitySystemComponent->InitAbilityActorInfo(this, this); 
	
	if (GEngine && attributeSet)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.0f,
			FColor::Green,
			FString::Printf(TEXT("HP: %.1f / %.1f | Stamina: %.1f / %.1f"),
				attributeSet->GetHealth(),
				attributeSet->GetMaxHealth(),
				attributeSet->GetStamina(),
				attributeSet->GetMaxStamina())
		);
	}
	
	for (TSubclassOf<UGAGameplayAbilityBase> abilityClass : defaultAbilities)
	{
		if (IsValid(abilityClass) == true)
		{
			abilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(abilityClass, 1, INDEX_NONE, this));
		}
	}
}

void ACombatPlayerCharacter::Tick(float DeltaSeconds){
	if (bIsLockOn && IsValid(currentLockOnTarget) == true)
	{
		FVector direction = currentLockOnTarget->GetActorLocation() - GetActorLocation();
		direction.Z = 0.0f;
		
		const FRotator targetRotation = direction.Rotation();
		const FRotator newRotation = FMath::RInterpTo(
			Controller->GetControlRotation(),
			targetRotation,
			DeltaSeconds,
			8.0f
			);
		
		if (IsValid(Controller) == true) Controller->SetControlRotation(newRotation);
	}
}

#pragma region Input

void ACombatPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent) == true)
	{
		if (IsValid(playerCharacterInputConfig) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("playerCharacterInputConfig Is Valid"));
			return;
		}
		EnhancedInputComponent->BindAction(playerCharacterInputConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
		EnhancedInputComponent->BindAction(playerCharacterInputConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
		EnhancedInputComponent->BindAction(playerCharacterInputConfig->LockOn, ETriggerEvent::Started, this, &ThisClass::InputLockOn);
		EnhancedInputComponent->BindAction(playerCharacterInputConfig->Zoom, ETriggerEvent::Triggered, this, &ThisClass::InputZoom);
		EnhancedInputComponent->BindAction(playerCharacterInputConfig->Attack, ETriggerEvent::Started, this, &ThisClass::InputAttack);
		EnhancedInputComponent->BindAction(playerCharacterInputConfig->Dodge, ETriggerEvent::Started, this, &ThisClass::InputDodge);
	}
}

void ACombatPlayerCharacter::InputMove(const FInputActionValue& InValue){
	FVector2D movementVector = InValue.Get<FVector2D>();
	
	if (!Controller) return;
	
	const FRotator controlRotation = Controller->GetControlRotation();
	const FRotator yawRotation(0.0f, controlRotation.Yaw, 0.0f);
	
	const FVector forward = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector right = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(forward, movementVector.X); 
	AddMovementInput(right, movementVector.Y);
}

void ACombatPlayerCharacter::InputLook(const FInputActionValue& Value){
	if (bIsLockOn) return;
	
	if (IsValid(GetController()) == true)
	{
		FVector2D LookVector = Value.Get<FVector2D>();
		
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void ACombatPlayerCharacter::InputLockOn(const FInputActionValue& InValue){
	if (bIsLockOn == false && TryLockOn() == true)
	{
		bIsLockOn = true;
	}
	else
	{
		ClearLockOn();
		bIsLockOn = false;
	}
}

void ACombatPlayerCharacter::InputZoom(const FInputActionValue& InValue){
	const float wheelValue = InValue.Get<float>();
	
	const float newArmLength = FMath::Clamp(
		springArmComponent->TargetArmLength - wheelValue * zoomSpeed, 
		minArmLength, 
		maxArmLength);
	
	springArmComponent->TargetArmLength = newArmLength;
}

void ACombatPlayerCharacter::InputAttack(const FInputActionValue& InValue){
	if (!abilitySystemComponent) return;
	UE_LOG(LogTemp, Warning, TEXT("InputAttack in Valid"));
	
	abilitySystemComponent->TryActivateAbilityByClass(UGAPlayerAttack::StaticClass());
}

void ACombatPlayerCharacter::InputDodge(const FInputActionValue& InValue){
	if (!abilitySystemComponent) return;
	UE_LOG(LogTemp, Warning, TEXT("InputDodge in Valid"));
	// 중복 입력 처리 하고싶은데 이러면 bIsDodge 를만들어서 처리해야하는데 그러면 GetbIsDodge도 만들어서 여기서 가져와서 처리해야하나 귀찮네
	abilitySystemComponent->TryActivateAbilityByClass(UGAPlayerDodge::StaticClass());
}

bool ACombatPlayerCharacter::TryLockOn(){
	TArray<AActor*> FoundActors;
	
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("LockOnTarget"), FoundActors);
	
	if (FoundActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputLockOn FoundActors Is valid"));
		return false;
	}

	AActor* bestTarget = nullptr;
	float bestDistance = 100000.0f;
	
	for (AActor* actor : FoundActors)
	{
		const float distance = FVector::Dist2D(GetActorLocation(), actor->GetActorLocation());
		
		if (distance < bestDistance)
		{
			bestDistance = distance;
			bestTarget = actor;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("actor is not in distance"));
			return false;
		}
	}
	
	if (IsValid(bestTarget) == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("currentLockOnTarget On"));
		currentLockOnTarget = bestTarget;
	}
	else UE_LOG(LogTemp, Warning, TEXT("InputLockOn bestTarget is Valid"));
	
	return IsValid(currentLockOnTarget);
}

void ACombatPlayerCharacter::ClearLockOn(){
	currentLockOnTarget = nullptr;
}

#pragma endregion 