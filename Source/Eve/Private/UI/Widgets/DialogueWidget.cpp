// Copyright aor9


#include "UI/Widgets/DialogueWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/DialogueStruct.h"
#include "UI/HUD/EveHUD.h"


void UDialogueWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NextBtn->OnClicked.AddDynamic(this, &UDialogueWidget::OnNextBtnClicked);
	EndBtn->OnClicked.AddDynamic(this, &UDialogueWidget::OnEndBtnClicked);
	FirstOptionBtn->OnClicked.AddDynamic(this, &UDialogueWidget::OnFirstOptionBtnClicked);
	SecondOptionBtn->OnClicked.AddDynamic(this, &UDialogueWidget::OnSecondOptionBtnClicked);
	ThirdOptionBtn->OnClicked.AddDynamic(this, &UDialogueWidget::OnThirdirstOptionBtnClicked);

	NextBtn->OnHovered.AddDynamic(this, &UDialogueWidget::OnNextBtnHovered);
	EndBtn->OnHovered.AddDynamic(this, &UDialogueWidget::OnEndBtnHovered);
	FirstOptionBtn->OnHovered.AddDynamic(this, &UDialogueWidget::OnFirstOptionBtnHovered);
	SecondOptionBtn->OnHovered.AddDynamic(this, &UDialogueWidget::OnSecondOptionBtnHovered);
	ThirdOptionBtn->OnHovered.AddDynamic(this, &UDialogueWidget::OnThirdirstOptionBtnHovered);

	NextBtn->OnUnhovered.AddDynamic(this, &UDialogueWidget::OnNextBtnUnhovered);
	EndBtn->OnUnhovered.AddDynamic(this, &UDialogueWidget::OnEndBtnUnhovered);
	FirstOptionBtn->OnUnhovered.AddDynamic(this, &UDialogueWidget::OnFirstOptionBtnUnhovered);
	SecondOptionBtn->OnUnhovered.AddDynamic(this, &UDialogueWidget::OnSecondOptionBtnUnhovered);
	ThirdOptionBtn->OnUnhovered.AddDynamic(this, &UDialogueWidget::OnThirdirstOptionBtnUnhovered);
}

void UDialogueWidget::ProcessDialogueOption(int32 OptionIndex)
{
	if (!InstanceDialogueData || !InstanceDialogueData->DataTable) return;
	if (!InstanceDialogueData->OptionData.IsValidIndex(OptionIndex)) return;

	FDialogueData* NextData = InstanceDialogueData->DataTable->
	FindRow<FDialogueData>(InstanceDialogueData->OptionData[OptionIndex].NextRow,TEXT("Find Next Dialogue"));

	if (!NextData)
	{
		UE_LOG(LogTemp, Warning, TEXT("다음 대사를 찾지 못함!"));
		return;
	}

	InstanceDialogueData = NextData;
	UpdateWidget(InstanceDialogueData);
}

void UDialogueWidget::OnNextBtnClicked()
{
	if (InstanceDialogueData && InstanceDialogueData->DataTable)
	{
		InstanceDialogueData = InstanceDialogueData->DataTable->
		FindRow<FDialogueData>(InstanceDialogueData->NextRow,TEXT("Find Next Dialogue"));

		if (InstanceDialogueData == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("다음 대사를 찾지 못함!"));
		}
		else
		{
			UpdateWidget(InstanceDialogueData);
		}
	}
}

void UDialogueWidget::OnEndBtnClicked()
{
	OwnerHUD->ToggleMainMenu(EMenuType::Dialogue);
}

void UDialogueWidget::OnFirstOptionBtnClicked()
{
	ProcessDialogueOption(0);
}

void UDialogueWidget::OnSecondOptionBtnClicked()
{
	ProcessDialogueOption(1);
}

void UDialogueWidget::OnThirdirstOptionBtnClicked()
{
	ProcessDialogueOption(2);
}

void UDialogueWidget::UpdateWidget(FDialogueData* DialogueData)
{
	InstanceDialogueData = DialogueData;
	NPCIcon->SetBrushFromTexture(DialogueData->NPCIcon);
	NameText->SetText(DialogueData->NPCName);
	DialogueText->SetText(DialogueData->DialogueText);

	if(DialogueData->bEndDialogue)
	{
		EndBtn->SetVisibility(ESlateVisibility::Visible);

		NextBtn->SetVisibility(ESlateVisibility::Collapsed);
		FirstOptionBtn->SetVisibility(ESlateVisibility::Collapsed);
		SecondOptionBtn->SetVisibility(ESlateVisibility::Collapsed);
		ThirdOptionBtn->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	
	if(DialogueData->OptionData.IsEmpty())
	{
		NextBtn->SetVisibility(ESlateVisibility::Visible);
		
		EndBtn->SetVisibility(ESlateVisibility::Collapsed);
		FirstOptionBtn->SetVisibility(ESlateVisibility::Collapsed);
		SecondOptionBtn->SetVisibility(ESlateVisibility::Collapsed);
		ThirdOptionBtn->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		NextBtn->SetVisibility(ESlateVisibility::Collapsed);
		EndBtn->SetVisibility(ESlateVisibility::Collapsed);
		FirstOptionBtn->SetVisibility(ESlateVisibility::Visible);
		SecondOptionBtn->SetVisibility(ESlateVisibility::Visible);
		ThirdOptionBtn->SetVisibility(ESlateVisibility::Visible);
		FirstOptionText->SetText(DialogueData->OptionData[0].OptionText);
		SecondOptionText->SetText(DialogueData->OptionData[1].OptionText);
		ThirdOptionText->SetText(DialogueData->OptionData[2].OptionText);
	}
}

void UDialogueWidget::OnNextBtnHovered()
{
	NextOptionText->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.7f, 0.2f)));
}

void UDialogueWidget::OnEndBtnHovered()
{
	EndOptionText->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.7f, 0.2f)));
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

void UDialogueWidget::OnEndBtnUnhovered()
{
	EndOptionText->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f)));
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