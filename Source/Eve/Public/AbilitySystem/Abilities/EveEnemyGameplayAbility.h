// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/EveGameplayAbility.h"
#include "EveEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AEveEnemyBase;
/**
 * 
 */
UCLASS()
class EVE_API UEveEnemyGameplayAbility : public UEveGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	AEveEnemyBase* GetEnemyFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AEveEnemyBase> CachedEveEnemy;
};
