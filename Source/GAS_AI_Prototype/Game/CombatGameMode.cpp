// CombatGameMode.cpp
#include "CombatGameMode.h"
#include "GAS_AI_Prototype/Character/Controller/CombatCharacterController.h"
#include "GAS_AI_Prototype/Character/Player/CombatPlayerCharacter.h"

ACombatGameMode::ACombatGameMode(){
	DefaultPawnClass = ACombatPlayerCharacter::StaticClass();
	PlayerControllerClass = ACombatCharacterController::StaticClass();
}
