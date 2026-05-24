// CombatPlayerCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GAS_AI_Prototype/Character/Base/CombatCharacterBase.h"
#include "CombatPlayerCharacter.generated.h"

UCLASS()
class GAS_AI_PROTOTYPE_API ACombatPlayerCharacter : public ACombatCharacterBase{
	GENERATED_BODY()

public:
	ACombatPlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	virtual void BeginPlay() override;
	
	
};
