// Copyright aor9


#include "AbilitySystem/Abilities/EveEnemyGameplayAbility.h"

#include "Character/EveEnemyBase.h"


AEveEnemyBase* UEveEnemyGameplayAbility::GetEnemyFromActorInfo()
{
	if(!CachedEveEnemy.IsValid())
	{
		CachedEveEnemy = Cast<AEveEnemyBase>(CurrentActorInfo->AvatarActor);
	}

	return CachedEveEnemy.IsValid() ? CachedEveEnemy.Get() : nullptr;
}

UEnemyCombatComponent* UEveEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyFromActorInfo()->GetEnemyCombatComponent();
}
