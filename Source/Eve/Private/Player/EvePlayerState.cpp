// Copyright aor9


#include "Player/EvePlayerState.h"

#include "AbilitySystem/EveAbilitySystemComponent.h"
#include "AbilitySystem/EveAttributeSet.h"


AEvePlayerState::AEvePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UEveAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UEveAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AEvePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
