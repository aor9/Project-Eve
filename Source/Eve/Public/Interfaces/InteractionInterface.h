// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "InteractionInterface.generated.h"

UINTERFACE(NotBlueprintable)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class EVE_API IInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnClick() = 0;
	
	UFUNCTION(BlueprintCallable)
	virtual void SetClickable(bool bActive) = 0;
};
