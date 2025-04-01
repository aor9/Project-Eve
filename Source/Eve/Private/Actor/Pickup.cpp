// Copyright aor9


#include "Actor/Pickup.h"

#include "EveDebugHelper.h"
#include "Components/WidgetComponent.h"
#include "Items/ItemBase.h"
#include "UI/Widgets/InteractionWidget.h"


class UInteractionWidget;

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("Pickup Mesh");
	SetRootComponent(PickupMesh);

	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidgetComponent->SetupAttachment(RootComponent);
	InteractionWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidgetComponent->SetVisibility(false);

	InteractionWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	InitPickup(ItemQuantity);
}

void APickup::InitPickup(const int32 InQuantity)
{
	if(ItemDataTable && !DesiredItemID.IsNone())
	{
		const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString());

		ItemReferecne = NewObject<UItemBase>(this, UItemBase::StaticClass());
		ItemReferecne->ID = ItemData->ID;
		ItemReferecne->ItemType = ItemData->ItemType;
		ItemReferecne->ItemQuality = ItemData->ItemQuality;
		ItemReferecne->ItemNumericData = ItemData->ItemNumericData;
		ItemReferecne->ItemTextData = ItemData->ItemTextData;
		ItemReferecne->ItemAssetData = ItemData->ItemAssetData;

		InQuantity <= 0 ? ItemReferecne->SetQuantity(1) : ItemReferecne->SetQuantity(InQuantity);
		PickupMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);

		UpdateInteractableData();
	}
}

void APickup::InitDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
	ItemReferecne = ItemToDrop;
	InQuantity <= 0 ? ItemReferecne->SetQuantity(1) : ItemReferecne->SetQuantity(InQuantity);
	ItemReferecne->ItemNumericData.Weight = ItemToDrop->GetItemSingleWeight();
	PickupMesh->SetStaticMesh(ItemToDrop->ItemAssetData.Mesh);
	 
	UpdateInteractableData();
}

void APickup::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.Action = ItemReferecne->ItemTextData.InteractionText;
	InstanceInteractableData.Name = ItemReferecne->ItemTextData.Name;
	InstanceInteractableData.Quantity = ItemReferecne->Quantity;
	InteractableData = InstanceInteractableData;
}


void APickup::BeginFocus()
{
	InteractionWidgetComponent->SetVisibility(true);

	UInteractionWidget* Widget = Cast<UInteractionWidget>(InteractionWidgetComponent->GetUserWidgetObject());
	if(Widget)
	{
		Widget->UpdateWidget(&InteractableData);
	}
}

void APickup::EndFocus()
{
	InteractionWidgetComponent->SetVisibility(false);
}

void APickup::Interact(AEveCharacter* EveCharacter)
{
	if(EveCharacter)
	{
		Debug::Print(TEXT("Interact"));
		TakePickup(EveCharacter);
	}
}

void APickup::TakePickup(const AEveCharacter* Taker)
{
	if(!IsPendingKillPending())
	{
		if(ItemReferecne)
		{
			// if(UInventoryComponent* PlayerInventory = Taker->GetInventory())

			// try to add item to player inventory
			// based on result of the add operation
			// adjust or destory the pickup
		}
	}
}

void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if(ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickup, DesiredItemID))
	{
		if(ItemDataTable)
		{
			if(const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString()))
			{
				PickupMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);
			}
		}
	}
}
