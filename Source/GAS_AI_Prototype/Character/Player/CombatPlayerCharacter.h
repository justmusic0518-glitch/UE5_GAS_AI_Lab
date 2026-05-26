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

UCLASS()
class GAS_AI_PROTOTYPE_API ACombatPlayerCharacter : public ACombatCharacterBase{
	GENERATED_BODY()

public:
	ACombatPlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> springArmComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> cameraComponent;
	
#pragma region Input
	
private: 
	void InputMove(const FInputActionValue& InValue);
	void InputLook(const FInputActionValue& Value);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UGAInputConfig> playerCharacterInputConfig;

#pragma endregion 
};
