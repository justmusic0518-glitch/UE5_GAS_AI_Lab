// CombatPlayerCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GAS_AI_Prototype/Character/Base/CombatCharacterBase.h"
#include "InputActionValue.h"
#include "CombatPlayerCharacter.generated.h"

class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class UGAInputConfig;
class UGAGameplayAbilityBase;

UCLASS()
class GAS_AI_PROTOTYPE_API ACombatPlayerCharacter : public ACombatCharacterBase{
	GENERATED_BODY()

public:
	ACombatPlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> springArmComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> cameraComponent;
	
#pragma region Input
	
private: 
	void InputMove(const FInputActionValue& InValue);
	void InputLook(const FInputActionValue& Value);
	void InputLockOn(const FInputActionValue& InValue);
	void InputZoom(const FInputActionValue& InValue);
	void InputAttack(const FInputActionValue& InValue);
	void InputDodge(const FInputActionValue& InValue);
	bool TryLockOn();
	void ClearLockOn();
	
	UPROPERTY()
	TObjectPtr<AActor> currentLockOnTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpringArm", meta = (AllowPrivateAccess))
	float minArmLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpringArm", meta = (AllowPrivateAccess))
	float maxArmLength;
	
	float zoomSpeed;
	bool bIsLockOn;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UGAInputConfig> playerCharacterInputConfig;

#pragma endregion 
	
#pragma region GAS
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGAGameplayAbilityBase>> defaultAbilities;
	
#pragma endregion 
};
