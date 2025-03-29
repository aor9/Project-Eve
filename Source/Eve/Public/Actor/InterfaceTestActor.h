// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "InterfaceTestActor.generated.h"

UCLASS()
class EVE_API AInterfaceTestActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AInterfaceTestActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnClick() override;
	UFUNCTION()
	virtual void SetClickable(bool bClickable) override;

private:
	bool bIsClickable = false;
	
};
