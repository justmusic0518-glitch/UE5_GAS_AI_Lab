// CombatAttributeSet.h
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "CombatAttributeSet.generated.h"

UCLASS()
class GAS_AI_PROTOTYPE_API UCombatAttributeSet : public UAttributeSet{
	GENERATED_BODY()
	
public:
	UCombatAttributeSet();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float maxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float stamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float maxStamina;
};
