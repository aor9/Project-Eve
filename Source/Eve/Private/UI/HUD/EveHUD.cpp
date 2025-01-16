// Copyright aor9


#include "UI/HUD/EveHUD.h"

#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/EveUserWidget.h"


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

