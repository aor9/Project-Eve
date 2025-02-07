// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Animation/EveBaseAnimInstance.h"
#include "EvePlayerLinkedAnimLayer.generated.h"

class UEvePlayerAnimInstance;
/**
 * 
 */
UCLASS()
class EVE_API UEvePlayerLinkedAnimLayer : public UEveBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UEvePlayerAnimInstance* GetPlayerAnimInstance() const;
	
};
