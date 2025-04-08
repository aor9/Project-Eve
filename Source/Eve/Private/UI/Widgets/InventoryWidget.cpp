// Copyright aor9


#include "UI/Widgets/InventoryWidget.h"

#include "EveDebugHelper.h"
#include "Character/EveCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Items/ItemBase.h"
#include "UI/ItemDragDropOperation.h"
#include "UI/Widgets/InventoryItemSlots.h"

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<AEveCharacter>(GetOwningPlayerPawn());
	if(PlayerCharacter)
	{
		InventoryReference = PlayerCharacter->GetInventory();
		if(InventoryReference)
		{
			InventoryReference->OnInventoryUpdated.AddUObject(this, &UInventoryWidget::RefreshInventory);
			SetInfoText();
		}
	}
}

void UInventoryWidget::SetInfoText() const
{
	const FString WeightInfoValue{
		FString::SanitizeFloat(InventoryReference->GetInventoryTotalWeight()) + "/"
		+ FString::SanitizeFloat(InventoryReference->GetWeightCapacity())
	};

	const FString CapacityInfoValue{
		FString::FromInt(InventoryReference->GetInventoryContents().Num()) + "/"
		+ FString::FromInt(InventoryReference->GetSlotsCapacity())
	};

	WeightInfo->SetText(FText::FromString(WeightInfoValue));
	CapacityInfo->SetText(FText::FromString(CapacityInfoValue));
}

void UInventoryWidget::RefreshInventory()
{
	if(InventoryReference && InventorySlotClass)
	{
		InventoryPanel->ClearChildren();

		for(TObjectPtr<UItemBase> const& InventoryItem : InventoryReference->GetInventoryContents())
		{
			UInventoryItemSlots* ItemSlot = CreateWidget<UInventoryItemSlots>(this, InventorySlotClass);
			ItemSlot->SetItemReference(InventoryItem);

			InventoryPanel->AddChildToWrapBox(ItemSlot);
		}
		
		SetInfoText();
	}
}

bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDropOperation = Cast<UItemDragDropOperation>(InOperation);

	if(ItemDragDropOperation->SourceItem && InventoryReference)
	{
		Debug::Print(TEXT("인벤토리 패널 위로 DROP 수행"));

		return true;
	}

	return false;
}
