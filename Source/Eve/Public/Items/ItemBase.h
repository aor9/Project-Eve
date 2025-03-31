// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "ItemBase.generated.h"

class AEveCharacter;
/**
 * 
 */
UCLASS()
class EVE_API UItemBase : public UObject
{
	GENERATED_BODY()
	

public:
	UItemBase();

	// UPROPERTY()
	// UInventoryComponent* OwningInventory;
	
	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName ID;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 Quantity;
	
	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemNumericData ItemNumericData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemAssetData ItemAssetData;

	UFUNCTION(Category = "Item")
	UItemBase* CreateItemCopy() const;

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use(AEveCharacter* Character);

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * ItemNumericData.Weight; }

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return ItemNumericData.Weight; }

	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity == ItemNumericData.MaxStackSize; }

protected:
	bool operator==(const FName& OtherID) const
	{
		return this->ID == OtherID;
	}

private:
	
};
