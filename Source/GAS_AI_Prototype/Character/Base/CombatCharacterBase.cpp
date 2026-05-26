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
