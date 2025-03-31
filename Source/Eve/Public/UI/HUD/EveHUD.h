// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EveHUD.generated.h"

struct FInteractableData;
class UInventoryWidget;
class UInteractionWidget;
class UMainMenuWidget;
class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UEveUserWidget;
struct FWidgetControllerParams;
/**
 * 
 */
UENUM()
enum class EWidgetLayer : uint8
{
	Background     = 0,
	Interaction	   = 5,
	HUD            = 10,
	Inventory      = 20,
	Popup          = 30,
	MainMenu       = 50
};


UCLASS()
class EVE_API AEveHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UEveUserWidget> OverlayWidget;

	bool bIsMenuVisible;

	AEveHUD();

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	void DisplayMenu();
	void HideMenu();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;
	
protected:
	UPROPERTY()
	UMainMenuWidget* MainMenuWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEveUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
};
