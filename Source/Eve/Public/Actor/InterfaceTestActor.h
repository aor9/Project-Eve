// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterfaceTestActor.generated.h"

UCLASS()
class EVE_API AInterfaceTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AInterfaceTestActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	
	
};
