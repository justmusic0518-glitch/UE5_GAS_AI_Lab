// GAPlayerAttack.cpp
#include "GAPlayerAttack.h"
#include "DrawDebugHelpers.h"
#include "GAS_AI_Prototype/Character/Base/CombatCharacterBase.h"

void UGAPlayerAttack::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UE_LOG(LogTemp, Warning, TEXT("Attack Ability Activated"));
	
	AActor* avatarActor = ActorInfo->AvatarActor.Get();
	ACombatCharacterBase* ownerCharacter = Cast<ACombatCharacterBase>(avatarActor);
	
	if (!ownerCharacter)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	UWorld* world = ownerCharacter->GetWorld();
	if (!world)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	const FVector startTrace = ownerCharacter->GetActorLocation() + ownerCharacter->GetActorForwardVector() * 80.0f;
	const FVector endTrace = startTrace + ownerCharacter->GetActorForwardVector() * 200.0f;
	const float radius = 80.0f;
	
	FCollisionQueryParams params;
	params.AddIgnoredActor(ownerCharacter);
	
	TArray<FHitResult> hitResults;
	
	const bool bHit = world->SweepMultiByChannel(
		hitResults,
		startTrace,
		endTrace,
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(radius),
		params
	);
	
	DrawDebugLine(world, startTrace, endTrace, FColor::Red, false, 2.0f, 0, 2.0f);
	DrawDebugSphere(world, endTrace, radius, 16, FColor::Red, false, 2.0f);
	
	if (bHit)
	{
		TSet<AActor*> damagedActors;
		
		for (const FHitResult& hit : hitResults)
		{
			AActor* hitActor = hit.GetActor();
			if (!hitActor || damagedActors.Contains(hitActor)) continue;
			
			ACombatCharacterBase* targetCharacter = Cast<ACombatCharacterBase>(hitActor);
			if (!targetCharacter) continue;
			
			targetCharacter->ApplyCombatDamage(25.0f);
			damagedActors.Add(hitActor);
		}
	}
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
