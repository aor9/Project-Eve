// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated)

class UItemBase;

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "NoItemAdded"),
	IAR_PartialAmountItemAdded UMETA(DisplayName = "PartialAmountItemAdded"),
	IAR_AllItemAdded UMETA(DisplayName = "ItemAdded")
};

USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_BODY()

	FItemAddResult()
		: ActualAmountAdded(0)
		, OperationResult(EItemAddResult::IAR_NoItemAdded)
		, ResultMessage(FText::GetEmpty())
	{
	};

	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 ActualAmountAdded;
	
	// Item 획득 결과를 저장하는 enum
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	EItemAddResult OperationResult;

	// 결과와 함께 들어갈 수 있는 메시지
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	FText ResultMessage;

	static FItemAddResult AddedNone(const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemAdded;
		AddedNoneResult.ResultMessage = ErrorText;

		return AddedNoneResult;
	};

	static FItemAddResult AddedPartial(const int32 PartialAmountAdded, const FText& Message)
	{
		FItemAddResult AddedPartialResult;
		AddedPartialResult.ActualAmountAdded = PartialAmountAdded;
		AddedPartialResult.OperationResult = EItemAddResult::IAR_PartialAmountItemAdded;
		AddedPartialResult.ResultMessage = Message;

		return AddedPartialResult;
	};
	
	static FItemAddResult AddedAll(const int32 AmountAdded, const FText& Message)
	{
		FItemAddResult AddedResult;
		AddedResult.ActualAmountAdded = AmountAdded;
		AddedResult.OperationResult = EItemAddResult::IAR_AllItemAdded;
		AddedResult.ResultMessage = Message;

		return AddedResult;
	};
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	
	FItemAddResult HandleAddItem(UItemBase* InputItem);
	
	UItemBase* FindMatchingItem(UItemBase* TargetItem) const;
	UItemBase* FindNextItemByID(UItemBase* TargetItem) const;
	UItemBase* FindNextPartialStack(UItemBase* TargetItem) const;
	
	void RemoveSingleInstanceOfItem(UItemBase* ItemToRemove);
	int32 RemoveAmountOfItem(UItemBase* TargetItem, int32 AmountToRemove);
	
	void SplitItemStacks(UItemBase* TargetItem, int32 AmountToSplit);

	// getters
	FORCEINLINE float GetInventoryTotalWeight() const { return InventoryTotalWeight; };
	FORCEINLINE float GetWeightCapacity() const { return InventoryWeightCapacity; };
	FORCEINLINE int32 GetSlotsCapacity() const { return InventorySlotsCapacity; };
	FORCEINLINE TArray<TObjectPtr<UItemBase>> GetInventoryContents() const { return InventoryContents;}; 

	// setters
	FORCEINLINE void SetSlotsCapacity(const int32 NewSlotsCpacity) {InventorySlotsCapacity = NewSlotsCpacity;};
	FORCEINLINE void SetWeightCapacity(const float NewWeightCapacity) {InventoryWeightCapacity = NewWeightCapacity;};

	FOnInventoryUpdated OnInventoryUpdated;

protected:
	virtual void BeginPlay() override;

	FItemAddResult HandleNoneStackableItems(UItemBase* TargetItem, int32 RequestedAddAmount);
	int32 HandleStackableItems(UItemBase* TargetItem, int32 RequestedAddAmount);
	int32 CalculateWeightAddAmount(UItemBase* TargetItem, int32 RequestedAddAmount);
	int32 CalculateNumberForFullStack(UItemBase* StackableItem, int32 RequestedAddAmount);

	void AddNewItem(UItemBase* Item, const int32 AmountToAdd);

	UPROPERTY(VisibleAnywhere, Category="Inventory")
	float InventoryTotalWeight;

	UPROPERTY(EditInstanceOnly, Category="Inventory")
	int32 InventorySlotsCapacity;

	UPROPERTY(VisibleAnywhere, Category="Inventory")
	int32 InventoryWeightCapacity;

	UPROPERTY(VisibleAnywhere, Category="Inventory")
	TArray<TObjectPtr<UItemBase>> InventoryContents;
	
private:
	
};
