// Copyright aor9


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/EveAbilitySystemComponent.h"


void UOverlayWidgetController::BroadcastInitValues()
{
	const UEveAttributeSet* EveAttributes = CastChecked<UEveAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(EveAttributes->GetHealth());
	OnMaxHealthChanged.Broadcast(EveAttributes->GetMaxHealth());

	OnBodyTemperatureChanged.Broadcast(EveAttributes->GetBodyTemperature());
	OnMaxBodyTemperatureChanged.Broadcast(EveAttributes->GetMaxBodyTemperature());
	
	OnHungerChanged.Broadcast(EveAttributes->GetHunger());
	OnMaxHungerChanged.Broadcast(EveAttributes->GetMaxHunger());
	
	OnStaminaChanged.Broadcast(EveAttributes->GetStamina());
	OnMaxStaminaChanged.Broadcast(EveAttributes->GetMaxStamina());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UEveAttributeSet* EveAttributes = CastChecked<UEveAttributeSet>(AttributeSet);

	// health
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnHealthChanged.Broadcast(Data.NewValue);}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnMaxHealthChanged.Broadcast(Data.NewValue);}
	);

	// body temperature
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetBodyTemperatureAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnBodyTemperatureChanged.Broadcast(Data.NewValue);}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetMaxBodyTemperatureAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnMaxBodyTemperatureChanged.Broadcast(Data.NewValue);}
	);

	// hunger
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetHungerAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnHungerChanged.Broadcast(Data.NewValue);}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetMaxHungerAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnMaxHungerChanged.Broadcast(Data.NewValue);}
	);

	// stamina
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnStaminaChanged.Broadcast(Data.NewValue);}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EveAttributes->GetStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnMaxStaminaChanged.Broadcast(Data.NewValue);}
	);

	Cast<UEveAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[](const FGameplayTagContainer& AssetTags)
		{
			for(const FGameplayTag &Tag : AssetTags)
			{
				//const FString Msg = FString::Printf(TEXT("GE Tag : %s"), *Tag.ToString());
				//GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Blue, Msg);
			}
		}
	);
}
