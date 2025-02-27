// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/PawnCombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class UGameplayEffect;
class AEvePlayerWeapon;
/**
 * 
 */
UCLASS()
class EVE_API UPlayerCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	AEvePlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag WeaponTag) const;
	
	void MeleeAttackTrace(FGameplayEffectSpecHandle DamageSpecHandle);
};
