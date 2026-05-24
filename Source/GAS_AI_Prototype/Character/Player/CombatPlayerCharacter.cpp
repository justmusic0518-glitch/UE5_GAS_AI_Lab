// CombatPlayerCharacter.cpp
#include "CombatPlayerCharacter.h"

ACombatPlayerCharacter::ACombatPlayerCharacter(){
	PrimaryActorTick.bCanEverTick = false;
}

void ACombatPlayerCharacter::BeginPlay(){
	Super::BeginPlay();
	
}

void ACombatPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

