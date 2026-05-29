// BossCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GAS_AI_Prototype/Character/Base/CombatCharacterBase.h"
#include "BossCharacter.generated.h"

UCLASS()
class GAS_AI_PROTOTYPE_API ABossCharacter : public ACombatCharacterBase{
	GENERATED_BODY()

public:
	ABossCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
