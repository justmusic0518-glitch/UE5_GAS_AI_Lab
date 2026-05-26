// CombatPlayerCharacter.cpp
#include "CombatPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GAS_AI_Prototype/Character/Input/GAInputConfig.h"
#include "Kismet/KismetSystemLibrary.h"

ACombatPlayerCharacter::ACombatPlayerCharacter(){
	PrimaryActorTick.bCanEverTick = false;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	// CharacterMovementComponent.h #include 
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	springArmComponent->SetupAttachment(RootComponent);
	springArmComponent->TargetArmLength = 500.0f;
	springArmComponent->bUsePawnControlRotation = true;
	
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComponent->SetupAttachment(springArmComponent);
	
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void ACombatPlayerCharacter::BeginPlay(){
	Super::BeginPlay();
		
	
}

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
	}
	
}

void ACombatPlayerCharacter::InputMove(const FInputActionValue& InValue){
	FVector2D movementVector = InValue.Get<FVector2D>();
	
	AddMovementInput(GetActorForwardVector(), movementVector.X);
	AddMovementInput(GetActorRightVector(), movementVector.Y);
}

void ACombatPlayerCharacter::InputLook(const FInputActionValue& Value){
	if (IsValid(GetController()) == true)
	{
		FVector2D LookVector = Value.Get<FVector2D>();
		
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

