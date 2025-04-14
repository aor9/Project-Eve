// Copyright aor9


#include "UI/Widgets/DialogueWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"


void UDialogueWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NextBtn->OnClicked.AddDynamic(this, &UDialogueWidget::OnNextBtnClicked);
	FirstOptionBtn->OnClicked.AddDynamic(this, &UDialogueWidget::OnFirstOptionBtnClicked);
	SecondOptionBtn->OnClicked.AddDynamic(this, &UDialogueWidget::OnSecondOptionBtnClicked);
	ThirdOptionBtn->OnClicked.AddDynamic(this, &UDialogueWidget::OnThirdirstOptionBtnClicked);

	NextBtn->OnHovered.AddDynamic(this, &UDialogueWidget::OnNextBtnHovered);

	FirstOptionBtn->OnHovered.AddDynamic(this, &UDialogueWidget::OnFirstOptionBtnHovered);
	SecondOptionBtn->OnHovered.AddDynamic(this, &UDialogueWidget::OnSecondOptionBtnHovered);
	ThirdOptionBtn->OnHovered.AddDynamic(this, &UDialogueWidget::OnThirdirstOptionBtnHovered);

	NextBtn->OnUnhovered.AddDynamic(this, &UDialogueWidget::OnNextBtnUnhovered);
	FirstOptionBtn->OnUnhovered.AddDynamic(this, &UDialogueWidget::OnFirstOptionBtnUnhovered);
	SecondOptionBtn->OnUnhovered.AddDynamic(this, &UDialogueWidget::OnSecondOptionBtnUnhovered);
	ThirdOptionBtn->OnUnhovered.AddDynamic(this, &UDialogueWidget::OnThirdirstOptionBtnUnhovered);
}

void UDialogueWidget::OnNextBtnClicked()
{
	
}

void UDialogueWidget::OnFirstOptionBtnClicked()
{
	
}

void UDialogueWidget::OnSecondOptionBtnClicked()
{
	
}

void UDialogueWidget::OnThirdirstOptionBtnClicked()
{
	
}

void UDialogueWidget::UpdateWidget(const FDialogueData* DialogueData) const
{
	// todo: 현재 dialogue에 따라 UI 업데이트.
}

void UDialogueWidget::OnNextBtnHovered()
{
	NextOptionText->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.7f, 0.2f)));
}

void UDialogueWidget::OnFirstOptionBtnHovered()
{
	FirstOptionText->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.7f, 0.2f)));
}

void UDialogueWidget::OnSecondOptionBtnHovered()
{
	SecondOptionText->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.7f, 0.2f)));
}

void UDialogueWidget::OnThirdirstOptionBtnHovered()
{
	ThirdOptionText->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.7f, 0.2f)));
}

void UDialogueWidget::OnNextBtnUnhovered()
{
	NextOptionText->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f)));
}

void UDialogueWidget::OnFirstOptionBtnUnhovered()
{
	FirstOptionText->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f)));
}

void UDialogueWidget::OnSecondOptionBtnUnhovered()
{
	SecondOptionText->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f)));
}

void UDialogueWidget::OnThirdirstOptionBtnUnhovered()
{
	ThirdOptionText->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f)));
}