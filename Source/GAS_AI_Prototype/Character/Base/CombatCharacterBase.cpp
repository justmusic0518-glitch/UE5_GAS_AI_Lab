// CombatCharacterBase.cpp
#include "CombatCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GAS_AI_Prototype/AbilitySystem/Attributes/CombatAttributeSet.h"

ACombatCharacterBase::ACombatCharacterBase(){
	PrimaryActorTick.bCanEverTick = false;
	
	abilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	attributeSet = CreateDefaultSubobject<UCombatAttributeSet>(TEXT("AttributeSet"));
}

void ACombatCharacterBase::BeginPlay(){
	Super::BeginPlay();
	
}

UAbilitySystemComponent* ACombatCharacterBase::GetAbilitySystemComponent() const{
	return abilitySystemComponent;
}


void ACombatCharacterBase::ApplyCombatDamage(float damageAmount){
	if (!attributeSet) return;
	
	if (bIsInvincible)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s ignored damage. Invincible."), *GetName());
		return;
	}
	
	const float oldHealth = attributeSet->GetHealth();
	const float newHealth = FMath::Clamp(oldHealth - damageAmount, 0.0f, attributeSet->GetMaxHealth());
	
	attributeSet->SetHealth(newHealth);
	
	UE_LOG(LogTemp, Warning, TEXT("%s HP: %.1f -> %.1f"), *GetName(), oldHealth, newHealth);
}

void ACombatCharacterBase::SetInvincible(bool bNewInvincible){
	bIsInvincible = bNewInvincible;
}

bool ACombatCharacterBase::IsInvincible() const{
	return bIsInvincible;
}
