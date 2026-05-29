// GAPlayerAttack.h
#pragma once

#include "CoreMinimal.h"
#include "GAS_AI_Prototype/AbilitySystem/Abilities/GAGameplayAbilityBase.h"
#include "GAPlayerAttack.generated.h"

UCLASS()
class GAS_AI_PROTOTYPE_API UGAPlayerAttack : public UGAGameplayAbilityBase{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData) override;
	
	
};
