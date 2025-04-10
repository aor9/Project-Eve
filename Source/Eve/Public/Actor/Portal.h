// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "Portal.generated.h"

class UWidgetComponent;

UCLASS()
class EVE_API APortal : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	APortal();
	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void Interact(AEveCharacter* EveCharacter) override;

protected:
	virtual void BeginPlay() override;

	void TravelToLevel() const;
	
	UPROPERTY(VisibleAnywhere, Category= "Portal")
	UStaticMeshComponent* PortalMesh;

	UPROPERTY(EditAnywhere, Category= "Portal")
	FName TargetLevelName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> InteractionWidgetComponent;
	
	UPROPERTY(VisibleInstanceOnly, Category= "Portal")
	FInteractableData InstanceInteractableData;
	
};
