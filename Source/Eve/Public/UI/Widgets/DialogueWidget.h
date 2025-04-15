// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

class AEveHUD;
class UButton;
struct FDialogueData;
class UTextBlock;
class UImage;
class UMainMenuWidget;

/**
 * 
 */
UCLASS()
class EVE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateWidget(FDialogueData* DialogueData);

	UPROPERTY()
	TObjectPtr<AEveHUD> OwnerHUD;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	void ProcessDialogueOption(int32 OptionIndex);

	UFUNCTION()
	void OnNextBtnClicked();
	
	UFUNCTION()
	void OnEndBtnClicked();

	UFUNCTION()
	void OnFirstOptionBtnClicked();

	UFUNCTION()
	void OnSecondOptionBtnClicked();

	UFUNCTION()
	void OnThirdirstOptionBtnClicked();

	UFUNCTION()
	void OnNextBtnHovered();

	UFUNCTION()
	void OnEndBtnHovered();

	UFUNCTION()
	void OnFirstOptionBtnHovered();

	UFUNCTION()
	void OnSecondOptionBtnHovered();

	UFUNCTION()
	void OnThirdirstOptionBtnHovered();

	UFUNCTION()
	void OnNextBtnUnhovered();
	
	UFUNCTION()
	void OnEndBtnUnhovered();

	UFUNCTION()
	void OnFirstOptionBtnUnhovered();

	UFUNCTION()
	void OnSecondOptionBtnUnhovered();

	UFUNCTION()
	void OnThirdirstOptionBtnUnhovered();


	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UImage* NPCIcon;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UTextBlock* NameText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UTextBlock* DialogueText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UButton* NextBtn;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UButton* EndBtn;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UButton* FirstOptionBtn;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UButton* SecondOptionBtn;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UButton* ThirdOptionBtn;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UTextBlock* NextOptionText;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UTextBlock* EndOptionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UTextBlock* FirstOptionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UTextBlock* SecondOptionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UTextBlock* ThirdOptionText;

private:
	FDialogueData* InstanceDialogueData;
	
};
