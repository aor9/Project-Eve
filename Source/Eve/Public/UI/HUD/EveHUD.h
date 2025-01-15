// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EveHUD.generated.h"

class UEveUserWidget;
/**
 * 
 */
UCLASS()
class EVE_API AEveHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UEveUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEveUserWidget> OverlayWidgetClass;
	
};
