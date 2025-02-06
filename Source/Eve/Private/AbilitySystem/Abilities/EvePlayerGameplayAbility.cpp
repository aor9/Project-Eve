// Copyright aor9


#include "AbilitySystem/Abilities/EvePlayerGameplayAbility.h"

#include "Character/EveCharacter.h"
#include "Player/EvePlayerController.h"


AEveCharacter* UEvePlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if(!CachedEvePlayerCharacter.IsValid())
	{
		CachedEvePlayerCharacter = Cast<AEveCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedEvePlayerCharacter.IsValid() ? CachedEvePlayerCharacter.Get() : nullptr;
}

AEvePlayerController* UEvePlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if(!CachedEvePlayerController.IsValid())
    {
    	CachedEvePlayerController = Cast<AEvePlayerController>(CurrentActorInfo->PlayerController);
    }
	
    return CachedEvePlayerController.IsValid() ? CachedEvePlayerController.Get() : nullptr;
}

UPlayerCombatComponent* UEvePlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}
