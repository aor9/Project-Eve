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
	UPROPERTY(EditAnywhere, Category = "TestActor")
	UStaticMeshComponent* Mesh;
	
	virtual void BeginPlay() override;
	
	virtual void Interact() override;
	
	virtual void BeginFocus() override;
	
	virtual void EndFocus() override;

	virtual void BeginInteract() override;

	virtual void EndInteract() override;

private:

	
};
