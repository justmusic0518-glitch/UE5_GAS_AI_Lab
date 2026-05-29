// CombatCharacterController.cpp
#include "CombatCharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

ACombatCharacterController::ACombatCharacterController(){
	
}

void ACombatCharacterController::BeginPlay(){
	Super::BeginPlay();
	
	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(subsystem) == true && IsValid(characterIMC) == true) subsystem->AddMappingContext(characterIMC, 0);
	
	FInputModeGameOnly inputMode;
	SetInputMode(inputMode);
	bShowMouseCursor = false;
}
