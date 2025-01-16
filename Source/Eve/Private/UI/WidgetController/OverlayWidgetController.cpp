// Copyright aor9


#include "UI/WidgetController/OverlayWidgetController.h"


void UOverlayWidgetController::BroadcastInitValues()
{
	const UEveAttributeSet* EveAttributes = CastChecked<UEveAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(EveAttributes->GetHealth());
	OnMaxHealthChanged.Broadcast(EveAttributes->GetMaxHealth());

	OnBodyTemperatureChanged.Broadcast(EveAttributes->GetBodyTemperature());
	OnMaxBodyTemperatureChanged.Broadcast(EveAttributes->GetMaxBodyTemperature());
	
	OnHungerChanged.Broadcast(EveAttributes->GetHunger());
	OnMaxHungerChanged.Broadcast(EveAttributes->GetMaxHunger());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UEveAttributeSet* EveAttributes = CastChecked<UEveAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetBodyTemperatureAttribute()).AddUObject(this, &UOverlayWidgetController::BodyTemperatureChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetMaxBodyTemperatureAttribute()).AddUObject(this, &UOverlayWidgetController::MaxBodyTemperatureChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetHungerAttribute()).AddUObject(this, &UOverlayWidgetController::HungerChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetMaxHungerAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHungerChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)	const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::BodyTemperatureChanged(const FOnAttributeChangeData& Data) const
{
	OnBodyTemperatureChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxBodyTemperatureChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxBodyTemperatureChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HungerChanged(const FOnAttributeChangeData& Data) const
{
	OnHungerChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHungerChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHungerChanged.Broadcast(Data.NewValue);
}
