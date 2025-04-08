// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryTooltip.generated.h"

class UInventoryItemSlots;
class UTextBlock;
/**
 * 
 */
UCLASS()
class EVE_API UInventoryTooltip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInventoryItemSlots> InventorySlotBeingHovered;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemType;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DamageValue;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ArmorRating;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UsageText;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemDescription;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SellValue;

protected:
	virtual void NativeConstruct() override;
	
	
};
