// CombatCharacterController.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CombatCharacterController.generated.h"

class UInputMappingContext;

UCLASS()
class GAS_AI_PROTOTYPE_API ACombatCharacterController : public APlayerController{
	GENERATED_BODY()
	
public:
	ACombatCharacterController();
	
private:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> characterIMC;
};
