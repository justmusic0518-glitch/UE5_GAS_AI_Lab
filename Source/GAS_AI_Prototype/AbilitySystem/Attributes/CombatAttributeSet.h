// CombatAttributeSet.h
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CombatAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GAS_AI_PROTOTYPE_API UCombatAttributeSet : public UAttributeSet{
	GENERATED_BODY()
	
public:
	UCombatAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, Category = "Status")	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Health)
	UPROPERTY(BlueprintReadOnly, Category = "Status")	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MaxHealth)
	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Stamina)
	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MaxStamina)


};
