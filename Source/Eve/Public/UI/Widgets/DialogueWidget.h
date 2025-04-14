// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

class UButton;
struct FDialogueData;
class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class EVE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateWidget(const FDialogueData* DialogueData) const;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnNextBtnClicked();

	UFUNCTION()
	void OnFirstOptionBtnClicked();

	UFUNCTION()
	void OnSecondOptionBtnClicked();

	UFUNCTION()
	void OnThirdirstOptionBtnClicked();

	UFUNCTION()
	void OnNextBtnHovered();

	UFUNCTION()
	void OnFirstOptionBtnHovered();

	UFUNCTION()
	void OnSecondOptionBtnHovered();

	UFUNCTION()
	void OnThirdirstOptionBtnHovered();

	UFUNCTION()
	void OnNextBtnUnhovered();

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
	UButton* FirstOptionBtn;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UButton* SecondOptionBtn;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UButton* ThirdOptionBtn;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UTextBlock* NextOptionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UTextBlock* FirstOptionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UTextBlock* SecondOptionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="DialogueWidget")
	UTextBlock* ThirdOptionText;
	
	
};
