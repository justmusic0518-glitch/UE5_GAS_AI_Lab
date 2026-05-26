// CombatCharacterBase.h
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

class UAbilitySystemComponent;
class IAbilitySystemInterface;
class UCombatAttributeSet;

UCLASS()
class GAS_AI_PROTOTYPE_API ACombatCharacterBase : public ACharacter, public IAbilitySystemInterface{
	GENERATED_BODY()

public:
	ACombatCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void BeginPlay() override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> abilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UCombatAttributeSet> attributeSet;
	
};
