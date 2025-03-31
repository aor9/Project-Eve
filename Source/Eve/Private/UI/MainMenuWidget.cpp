// Copyright aor9


#include "UI/MainMenuWidget.h"

#include "Character/EveCharacter.h"


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
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	
}
