// BossCharacter.cpp
#include "BossCharacter.h"

ABossCharacter::ABossCharacter(){
	PrimaryActorTick.bCanEverTick = false;
}

void ABossCharacter::BeginPlay(){
	Super::BeginPlay();
	
}

void ABossCharacter::Tick(float DeltaTime){ Super::Tick(DeltaTime); }

void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

