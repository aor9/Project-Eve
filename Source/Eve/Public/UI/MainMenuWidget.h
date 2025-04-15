// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UDialogueWidget;
class UInventoryWidget;
class AEveCharacter;
/**
 * 
 */
UCLASS()
class EVE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	AEveCharacter* EveCharacter;

	UPROPERTY(meta = (BindWidget))
	UInventoryWidget* InventoryWidget;

	UPROPERTY(meta = (BindWidget))
	UDialogueWidget* DialogueWidget;
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	
	
};
