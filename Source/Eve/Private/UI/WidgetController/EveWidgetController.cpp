// Copyright aor9


#include "UI/WidgetController/EveWidgetController.h"


void UEveWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet = WidgetControllerParams.AttributeSet;
}

void UEveWidgetController::BroadcastInitValues()
{
	
}

void UEveWidgetController::BindCallbacksToDependencies()
{
	
}
