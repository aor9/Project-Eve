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

UENUM(BlueprintType)
enum class EMenuType : uint8
{
	MainMenu,
	Inventory,
	Dialogue,
	Shop
};


UCLASS()
class EVE_API AEveHUD : public AHUD
{
	GENERATED_BODY()

public:
	AEveHUD();

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	void DisplayMainMenu(EMenuType MenuType);
	void HideMainMenu(EMenuType MenuType);
	void ToggleMainMenu(EMenuType MenuType);

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;
	
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UEveUserWidget> OverlayWidget;

	bool bIsMenuVisible;

	FORCEINLINE UMainMenuWidget* GetMainMenuWidget() const { return MainMenuWidget; }
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UMainMenuWidget* MainMenuWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEveUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
};
