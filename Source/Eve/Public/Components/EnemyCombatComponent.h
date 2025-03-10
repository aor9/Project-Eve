// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	void MeleeAttackTrace(FGameplayEffectSpecHandle DamageSpecHandle);
	
};
