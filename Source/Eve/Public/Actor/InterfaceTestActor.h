// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "InterfaceTestActor.generated.h"

class UWidgetComponent;
class AEveCharacter;

UCLASS()
class EVE_API AInterfaceTestActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AInterfaceTestActor();

protected:
	UPROPERTY(EditAnywhere, Category = "TestActor")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, Category="TestActor")
	FInteractableData InstanceInteractableData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> InteractionWidgetComponent;
	
	virtual void BeginPlay() override;
	virtual void Interact(AEveCharacter* Character) override;
	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void EndInteract() override;

private:

	
};
