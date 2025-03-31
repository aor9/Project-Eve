// Copyright aor9


#include "UI/HUD/EveHUD.h"

#include "UI/MainMenuWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/EveUserWidget.h"
#include "UI/Widgets/InteractionWidget.h"


AEveHUD::AEveHUD()
{
	
}

void AEveHUD::BeginPlay()
{
	Super::BeginPlay();

	if(MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		MainMenuWidget->AddToViewport(static_cast<int32>(EWidgetLayer::MainMenu));
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if(InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(static_cast<int32>(EWidgetLayer::Interaction));
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

UOverlayWidgetController* AEveHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();

		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}

void AEveHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("overlay widget class uninitialized, please fill out BP_EveHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("overlay widget controller class uninitialized, please fill out BP_EveHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UEveUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->InitWidgetController(WidgetController);
	WidgetController->BroadcastInitValues();
	
	Widget->AddToViewport();
}

void AEveHUD::DisplayMenu()
{
	if(MainMenuWidget)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AEveHUD::HideMenu()
{
	if(MainMenuWidget)
	{
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AEveHUD::ShowInteractionWidget() const
{
	if(InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AEveHUD::HideInteractionWidget() const
{
	if(InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AEveHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if(InteractionWidget)
	{
		if(InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateWidget(InteractableData);
	}
}

