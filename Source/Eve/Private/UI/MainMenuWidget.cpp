// Copyright aor9


#include "UI/MainMenuWidget.h"

#include "Character/EveCharacter.h"
#include "Items/ItemBase.h"
#include "UI/ItemDragDropOperation.h"


void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EveCharacter = Cast<AEveCharacter>(GetOwningPlayerPawn());
}

bool UMainMenuWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	if(EveCharacter && ItemDragDrop->SourceItem)
	{
		EveCharacter->DropItem(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->Quantity);
		return true;
	}
	
	return false;
}
