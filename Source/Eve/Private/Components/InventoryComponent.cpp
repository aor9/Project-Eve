// Copyright aor9


#include "Components/InventoryComponent.h"

#include "Items/ItemBase.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

UItemBase* UInventoryComponent::FindMatchingItem(UItemBase* TargetItem) const
{
	if(TargetItem)
	{
		if(InventoryContents.Contains(TargetItem))
		{
			return TargetItem;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextItemByID(UItemBase* TargetItem) const
{
	if(TargetItem)
	{
		if(const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(TargetItem))
		{
			return *Result;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(UItemBase* TargetItem) const
{
	// 스택이 아직 다 안 찬 같은 종류의 아이템 리턴
	if(const TArray<TObjectPtr<UItemBase>>::ElementType* Result =
		InventoryContents.FindByPredicate([&TargetItem](const UItemBase* InventoryItem)
		{
			return InventoryItem->ID == TargetItem->ID && !InventoryItem->IsFullItemStack();
		}))
	{
		return *Result;
	}

	return nullptr;
}

int32 UInventoryComponent::CalculateWeightAddAmount(UItemBase* TargetItem, int32 RequestedAddAmount)
{
	const int32 WeightMaxAddAmount = FMath::FloorToInt((GetWeightCapacity() - InventoryTotalWeight) / TargetItem->GetItemSingleWeight());
	if(WeightMaxAddAmount >= RequestedAddAmount)
	{
		return RequestedAddAmount;
	}
	return WeightMaxAddAmount;
}

int32 UInventoryComponent::CalculateNumberForFullStack(UItemBase* StackableItem, int32 RequestedAddAmount)
{
	// 채울 수 있는 수량, 요청 수량 비교해서 최대한 넣기
	const int32 AddAmountToMakeFullStack = StackableItem->ItemNumericData.MaxStackSize - StackableItem->Quantity;

	return FMath::Min(RequestedAddAmount, AddAmountToMakeFullStack);
}

void UInventoryComponent::RemoveSingleInstanceOfItem(UItemBase* ItemToRemove)
{
	InventoryContents.RemoveSingle(ItemToRemove);
	OnInventoryUpdated.Broadcast();
}

int32 UInventoryComponent::RemoveAmountOfItem(UItemBase* TargetItem, int32 AmountToRemove)
{
	const int32 ActualAmountToRemove= FMath::Min(AmountToRemove, TargetItem->Quantity);

	TargetItem->SetQuantity(TargetItem->Quantity - ActualAmountToRemove);

	InventoryTotalWeight -= ActualAmountToRemove * TargetItem->GetItemSingleWeight();

	OnInventoryUpdated.Broadcast();

	return ActualAmountToRemove;
}

void UInventoryComponent::SplitItemStacks(UItemBase* TargetItem, int32 AmountToSplit)
{
	if(!(InventoryContents.Num() + 1 > InventorySlotsCapacity))
	{
		RemoveAmountOfItem(TargetItem, AmountToSplit);
		AddNewItem(TargetItem, AmountToSplit);
	}
}

FItemAddResult UInventoryComponent::HandleNoneStackableItems(UItemBase* TargetItem, int32 RequestedAddAmount)
{
	// check if in the input item has valid weight
	if (FMath::IsNearlyZero(TargetItem->GetItemSingleWeight()) || TargetItem->GetItemSingleWeight() < 0)
	{
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to the inventory. Item has invalid weight value."),
			TargetItem->ItemTextData.Name));
	}

	// will the item weight overflow weight capacity
	if (InventoryTotalWeight + TargetItem->GetItemSingleWeight() > GetWeightCapacity())
	{
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to the inventory. Item would overflow weight limit."),
			TargetItem->ItemTextData.Name));
	}

	// adding one more item would overflow slot capacity
	if (InventoryContents.Num() + 1 > InventorySlotsCapacity)
	{
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to the inventory. All inventory slots are full."),
			TargetItem->ItemTextData.Name));
	}

	AddNewItem(TargetItem, 1);
	
	return FItemAddResult::AddedAll(1, FText::Format(
		FText::FromString("Successfully added a single {0} to the inventory."), TargetItem->ItemTextData.Name));
}

int32 UInventoryComponent::HandleStackableItems(UItemBase* TargetItem, int32 RequestedAddAmount)
{
	return 0;
}

FItemAddResult UInventoryComponent::HandleAddItem(UItemBase* InputItem)
{
	if(GetOwner())
	{
		const int32 RequestedAddAmount = InputItem->Quantity;

		// handle none stackable items
		if(!InputItem->ItemNumericData.bIsStackable)
		{
			return HandleNoneStackableItems(InputItem, RequestedAddAmount);
		}

		// handle stackable items
		const int32 StackableAmountAdded = HandleStackableItems(InputItem, RequestedAddAmount);

		if(StackableAmountAdded == RequestedAddAmount)
		{
			// return added all result
		}

		if(StackableAmountAdded < RequestedAddAmount && StackableAmountAdded > 0)
		{
			// return added partial result
		}

		if(StackableAmountAdded <= 0)
		{
			// return added none result
		}
	}
	
	check(false);
	return FItemAddResult::AddedNone(FText::FromString("TryAddItem fallthrough error. GetOwner() check somehow failed."));
}

void UInventoryComponent::AddNewItem(UItemBase* Item, const int32 AmountToAdd)
{
	UItemBase* NewItem;

	if (Item->bIsCopy || Item->bIsPickup)
	{
		// if the item is already a copy, or is a world pickup
		NewItem = Item;
		NewItem->ResetItemFlags();
	}
	else
	{
		// used when splitting or dragging to/from another inventory
		NewItem = Item->CreateItemCopy();
	}

	NewItem->OwningInventory = this;
	NewItem->SetQuantity(AmountToAdd);

	InventoryContents.Add(NewItem);
	InventoryTotalWeight += NewItem->GetItemStackWeight();
	OnInventoryUpdated.Broadcast();
}

