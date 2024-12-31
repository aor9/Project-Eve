// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EveGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API UEveGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UEveGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	virtual void Init() override;
	virtual void Shutdown() override;
	
	
};
