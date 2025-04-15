// Copyright aor9


#include "Components/DialogueComponent.h"

#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MainMenuWidget.h"
#include "UI/HUD/EveHUD.h"
#include "UI/Widgets/DialogueWidget.h"


UDialogueComponent::UDialogueComponent()
{
}

void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	if(DialogueDataTable)
	{
		InstanceDialogueData = *DialogueDataTable->FindRow<FDialogueData>(StartRowName, TEXT("Start Dialogue Row Lookup"));
	}
}

void UDialogueComponent::StartDialogue()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (AEveHUD* HUD = Cast<AEveHUD>(PC->GetHUD()))
		{
			HUD->GetMainMenuWidget()->DialogueWidget->UpdateWidget(&InstanceDialogueData);
			HUD->ToggleMainMenu(EMenuType::Dialogue);
		}
	}
}
