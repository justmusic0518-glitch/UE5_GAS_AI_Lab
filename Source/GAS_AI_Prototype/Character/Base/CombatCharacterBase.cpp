// CombatCharacterBase.cpp
#include "CombatCharacterBase.h"
#include "AbilitySystemComponent.h"

ACombatCharacterBase::ACombatCharacterBase(){
	PrimaryActorTick.bCanEverTick = false;
	
	abilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void ACombatCharacterBase::BeginPlay(){
	Super::BeginPlay();
	
}

UAbilitySystemComponent* ACombatCharacterBase::GetAbilitySystemComponent() const{
	return abilitySystemComponent;
}
