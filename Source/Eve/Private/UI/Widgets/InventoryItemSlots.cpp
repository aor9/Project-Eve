// Copyright aor9


#include "UI/Widgets/InventoryItemSlots.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/ItemBase.h"
#include "UI/ItemDragDropOperation.h"
#include "UI/Widgets/DragItemVisual.h"
#include "UI/Widgets/InventoryTooltip.h"


void UInventoryItemSlots::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(InventoryToolTipClass)
	{
		UInventoryTooltip* ToolTip = CreateWidget<UInventoryTooltip>(this, InventoryToolTipClass);
		ToolTip->InventorySlotBeingHovered = this;
		SetToolTip(ToolTip);
	}
}

void UInventoryItemSlots::NativeConstruct()
{
	Super::NativeConstruct();

	if(ItemReference)
	{
		ItemBorder->SetBrushColor(FLinearColor::Gray);
		ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
		if(ItemReference->ItemNumericData.bIsStackable)
		{
			ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
		}
		else
		{
			ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

FReply UInventoryItemSlots::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if(InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	if(InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		//todo: submenu on right click will happen here
	}

	return Reply.Unhandled();
}

void UInventoryItemSlots::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void UInventoryItemSlots::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if(DragItemVisualClass)
	{
		const TObjectPtr<UDragItemVisual> DragItemVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualClass);
		DragItemVisual->ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
		DragItemVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());
		DragItemVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));

		UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();
		DragItemOperation->SourceItem = ItemReference;
		DragItemOperation->SourceInventory = ItemReference->OwningInventory;
		DragItemOperation->DefaultDragVisual = DragItemVisual;
		DragItemOperation->Pivot = EDragPivot::TopLeft;

		OutOperation = DragItemOperation;
	}
}

bool UInventoryItemSlots::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
