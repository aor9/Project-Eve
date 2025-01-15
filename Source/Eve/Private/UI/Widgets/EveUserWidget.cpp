// Copyright aor9


#include "UI/Widgets/EveUserWidget.h"


void UEveUserWidget::InitWidgetController(UObject* InWidgetController)
{
	if(InWidgetController)
	{
		WidgetController = InWidgetController;
		OnWidgetControllerInit();
	}
}
