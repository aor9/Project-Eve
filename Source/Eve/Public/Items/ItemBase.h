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

	UPROPERTY(VisibleAnywhere, Category = "ItemData", meta = (UIMin = 1, UIMax = 100))
	int32 Quantity;
	
	UPROPERTY(EditAnywhere, Category = "ItemData")
	FName ID;
	
	UPROPERTY(EditAnywhere, Category = "ItemData")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemNumericData ItemNumericData;

	UPROPERTY(EditAnywhere, Category = "ItemData")
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
		return ID == OtherID;
	}

private:
	
};
