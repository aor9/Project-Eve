// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/EveWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBodyTemperatureChangedSignature, float, NewBodyTemperature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxBodyTemperatureChangedSignature, float, NewMaxBodyTemperature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHungerChangedSignature, float, NewHunger);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHungerChangedSignature, float, NewMaxHunger);

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
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnBodyTemperatureChangedSignature OnBodyTemperatureChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxBodyTemperatureChangedSignature OnMaxBodyTemperatureChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHungerChangedSignature OnHungerChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHungerChangedSignature OnMaxHungerChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

	void BodyTemperatureChanged(const FOnAttributeChangeData& Data) const;
	void MaxBodyTemperatureChanged(const FOnAttributeChangeData& Data) const;
	
	void HungerChanged(const FOnAttributeChangeData& Data) const;
	void MaxHungerChanged(const FOnAttributeChangeData& Data) const;
};
