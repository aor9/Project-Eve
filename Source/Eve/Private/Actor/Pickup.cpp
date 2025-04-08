// Copyright aor9


#include "Actor/Pickup.h"

#include "EveDebugHelper.h"
#include "Components/InventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "Items/ItemBase.h"
#include "Player/EvePlayerController.h"
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
	
	if(UInteractionWidget* Widget = Cast<UInteractionWidget>(InteractionWidgetComponent->GetUserWidgetObject()))
	{
		Widget->UpdateWidget(&InteractableData);
	}
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

	if(UInteractionWidget* Widget = Cast<UInteractionWidget>(InteractionWidgetComponent->GetUserWidgetObject()))
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
			if(UInventoryComponent* PlayerInventory = Taker->GetInventory())
			{
				const FItemAddResult AddResult = PlayerInventory->HandleAddItem(ItemReferecne);

				switch (AddResult.OperationResult)
				{
				case EItemAddResult::IAR_NoItemAdded:
					break;
				case EItemAddResult::IAR_PartialAmountItemAdded:
					{
						UpdateInteractableData();
						AEvePlayerController* PC = Cast<AEvePlayerController>(Taker->GetController());
						PC->UpdateInteractionWidget();
						break;	
					}
				case EItemAddResult::IAR_AllItemAdded:
					{
						Destroy();
						break;	
					}
				default:
					break;
				}

				UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Player inventory component is null!!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup internal item reference was null!"));
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
