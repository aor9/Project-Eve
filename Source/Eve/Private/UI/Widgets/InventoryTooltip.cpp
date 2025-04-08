// Copyright aor9


#include "UI/Widgets/InventoryTooltip.h"

#include "Components/TextBlock.h"
#include "Items/ItemBase.h"
#include "UI/Widgets/InventoryItemSlots.h"


void UInventoryTooltip::NativeConstruct()
{
	Super::NativeConstruct();
	

	if(const UItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference())
	{
		switch (ItemBeingHovered->ItemQuality)
		{
		case EItemQuality::Normal:
			ItemType->SetColorAndOpacity(FLinearColor::Gray);
			break;
		case EItemQuality::Magic:
			ItemType->SetColorAndOpacity(FLinearColor::Blue);
			break;
		case EItemQuality::Rare:
			ItemType->SetColorAndOpacity(FLinearColor::Yellow);
			break;
		case EItemQuality::Unique:
			ItemType->SetColorAndOpacity(FLinearColor::Red);
			break;
		default:
			break;
		}
		
		switch (ItemBeingHovered->ItemType)
		{
		case EItemType::Armor:
			break;
		case EItemType::Weapon:
			break;
		case EItemType::Shield:
			break;
		case EItemType::Spell:
			break;
		case EItemType::Consumable:
			ItemType->SetText(FText::FromString("Consumable"));
			DamageValue->SetVisibility(ESlateVisibility::Collapsed);
			ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
			break;
		case EItemType::Quest:
			break;
		case EItemType::Mundane:
			ItemType->SetText(FText::FromString("Mundane"));
			DamageValue->SetVisibility(ESlateVisibility::Collapsed);
			ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
			UsageText->SetVisibility(ESlateVisibility::Collapsed);
			break;
		default: ;
		}

		ItemName->SetText(ItemBeingHovered->ItemTextData.Name);
		DamageValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.DamageValue));
		ArmorRating->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.ArmorRating));
		UsageText->SetText(ItemBeingHovered->ItemTextData.UsageText);
		ItemDescription->SetText(ItemBeingHovered->ItemTextData.Description);
		SellValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.SellValue));

		const FString WeightInfo =
			{"Weight: " + FString::SanitizeFloat(ItemBeingHovered->GetItemStackWeight()) };
	}
}
