// Copyright aor9


#include "UI/HUD/EveHUD.h"

#include "UI/Widgets/EveUserWidget.h"


void AEveHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
