// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EveCharacterBase.generated.h"

UCLASS()
class EVE_API AEveCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEveCharacterBase();

protected:
	virtual void BeginPlay() override;
	
};
