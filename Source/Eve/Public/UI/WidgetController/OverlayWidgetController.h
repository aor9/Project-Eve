// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/EveWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UEveUserWidget;

// 아이템 획득이나 이벤트 발생시 사용 할 팝업 UI
// TODO: DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemAcquired, const FGameplayTag&) 델리게이트 만들기
USTRUCT(BlueprintType)
struct FItemPopupUI : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UEveUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* BackgroundImage = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature, float, NewValue);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class EVE_API UOverlayWidgetController : public UEveWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSignature OnBodyTemperatureChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSignature OnMaxBodyTemperatureChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSignature OnHungerChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSignature OnMaxHungerChanged;
	
};
