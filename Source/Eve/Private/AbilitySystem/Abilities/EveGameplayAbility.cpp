// Copyright aor9


#include "AbilitySystem/Abilities/EveGameplayAbility.h"

#include "AbilitySystem/EveAttributeSet.h"


FString UEveGameplayAbility::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"), L"Default Ability Name - LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum", Level);
}

float UEveGameplayAbility::GetCooldown(float InLevel) const
{
	float Cooldown = 0.f;
	
	if (const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect())
	{
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, Cooldown);
	}
	
	return Cooldown;
}

float UEveGameplayAbility::GetStaminaCost(float InLevel) const
{
	float StaminaCost = 0.f;
	
	if (const UGameplayEffect* CostEffect = GetCostGameplayEffect())
	{
		for (FGameplayModifierInfo Mod : CostEffect->Modifiers)
		{
			if (Mod.Attribute == UEveAttributeSet::GetStaminaAttribute())
			{
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, StaminaCost);
				break;
			}
		}
	}
	
	return StaminaCost;
}
