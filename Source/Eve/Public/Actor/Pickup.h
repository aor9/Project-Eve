// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Character/EveCharacter.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "Pickup.generated.h"

class UItemBase;

UCLASS()
class EVE_API APickup : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:
	APickup();

	void InitPickup(const int32 InQuantity);

	void InitDrop(UItemBase* ItemToDrop, const int32 InQuantity);

	FORCEINLINE UItemBase* GetItemData() { return ItemReferecne; }

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void Interact(AEveCharacter* EveCharacter) override;

protected:
	virtual void BeginPlay() override;

	void UpdateInteractableData();
	
	void TakePickup(const AEveCharacter* Taker);
	
	UPROPERTY(VisibleAnywhere, Category= "Pickup | Components")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditInstanceOnly, Category= "Pickup | Item Init")
	UDataTable* ItemDataTable;

	UPROPERTY(EditInstanceOnly, Category= "Pickup | Item Init")
	FName DesiredItemID;
	
	UPROPERTY(EditInstanceOnly, Category= "Pickup | Item Init")
	int32 ItemQuantity;

	UPROPERTY(VisibleAnywhere, Category= "Pickup | Item Reference")
	UItemBase* ItemReferecne;

	UPROPERTY(VisibleInstanceOnly, Category= "Pickup | Interaction")
	FInteractableData InstanceInteractableData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> InteractionWidgetComponent;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
