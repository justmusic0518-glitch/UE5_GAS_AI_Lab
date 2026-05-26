// GAInputConfig.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GAInputConfig.generated.h"

class UInputAction;

UCLASS()
class GAS_AI_PROTOTYPE_API UGAInputConfig : public UDataAsset{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Look;
};
