// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EveUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API UEveUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerInit();
	
};
