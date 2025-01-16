// Copyright aor9


#include "AbilitySystem/EveAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"


UEveAttributeSet::UEveAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitBodyTemperature(0.5f);
	InitMaxBodyTemperature(1.f);
	InitHunger(0.5f);
	InitMaxHunger(1.f);
	
	InitStamina(1.f);
	InitMaxStamina(1.f);
}

void UEveAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, BodyTemperature, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, MaxBodyTemperature, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, Hunger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, MaxHunger, COND_None, REPNOTIFY_Always);
}

void UEveAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, Health, OldHealth);
}

void UEveAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, MaxHealth, OldMaxHealth);
}

void UEveAttributeSet::OnRep_BodyTemperature(const FGameplayAttributeData& OldBodyTemperature) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, BodyTemperature, OldBodyTemperature);
}

void UEveAttributeSet::OnRep_MaxBodyTemperature(const FGameplayAttributeData& OldMaxBodyTemperature) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, MaxBodyTemperature, OldMaxBodyTemperature);
}

void UEveAttributeSet::OnRep_Hunger(const FGameplayAttributeData& OldHunger) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, Hunger, OldHunger);
}

void UEveAttributeSet::OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, MaxHunger, OldMaxHunger);
}

void UEveAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, Stamina, OldStamina);
}

void UEveAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, MaxStamina, OldMaxStamina);
}
