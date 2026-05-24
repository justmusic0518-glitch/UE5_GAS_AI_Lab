// CombatCharacterBase.h
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

class UAbilitySystemComponent;
class IAbilitySystemInterface;
class UAttributeSet;

UCLASS()
class GAS_AI_PROTOTYPE_API ACombatCharacterBase : public ACharacter, public IAbilitySystemInterface{
	GENERATED_BODY()

public:
	ACombatCharacterBase();

protected:
	virtual void BeginPlay() override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> abilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAttributeSet> attributeSet;
	
};
