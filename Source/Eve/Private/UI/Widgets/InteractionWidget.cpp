// Copyright aor9


#include "UI/Widgets/InteractionWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interfaces/InteractionInterface.h"

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	KeyPressText->SetText(FText::FromString("Press"));
	CurrentInteractionDuration = 0.f;
}


void UInteractionWidget::UpdateWidget(const FInteractableData* InteractableData) const
{
	switch (InteractableData->InteractableType)
	{
	case Pickup:
		KeyPressText->SetVisibility(ESlateVisibility::Collapsed);
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		if(InteractableData->Quantity < 2)
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			QuantityText->SetText(FText::Format(NSLOCTEXT("InteractionWidget", "QuantityText", "x{0}"),
				InteractableData->Quantity));
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}
		break;
		
	case NonPlayerCharacter:
		break;
	
	case Device:
		break;
	
	case Toggle:
		KeyPressText->SetVisibility(ESlateVisibility::Collapsed);
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		break;
	
	case Container:
		break;

	default:
		break;
	}

	ActionText->SetText(InteractableData->Action);
	NameText->SetText(InteractableData->Name);
}

float UInteractionWidget::UpdateInteractionProgress()
{
	return 0.f;
}