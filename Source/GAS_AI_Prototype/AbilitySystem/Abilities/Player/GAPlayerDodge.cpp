// GAPlayerDodge.cpp
#include "GAPlayerDodge.h"
#include "GAS_AI_Prototype/Character/Base/CombatCharacterBase.h"

void UGAPlayerDodge::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UE_LOG(LogTemp, Warning, TEXT("Dodge Ability Activated"));
	
	ACombatCharacterBase* ownerCharacter = Cast<ACombatCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!ownerCharacter)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	
	ownerCharacter->SetInvincible(true);
	UE_LOG(LogTemp, Warning, TEXT("Dodge Start: Invincible On"));
	
	FTimerHandle TimerHandle;
	
	ownerCharacter->GetWorldTimerManager().SetTimer(
		TimerHandle,
		FTimerDelegate::CreateWeakLambda(ownerCharacter, [ownerCharacter, Handle, ActorInfo, ActivationInfo, this]()
		{
			ownerCharacter->SetInvincible(false);
			UE_LOG(LogTemp, Warning, TEXT("Dodge End: Invincible OFF"));
			
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		}),
		0.5f,
		false
		);
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
