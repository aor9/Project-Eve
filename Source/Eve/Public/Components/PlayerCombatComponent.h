// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/PawnCombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class AEveEnemyBase;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UCameraShakeBase> CombatCameraShake;
	
	void MeleeAttackTrace(FGameplayEffectSpecHandle DamageSpecHandle);
	
	void PlayCombatCameraShake() const;
	void PlayHitReact(ACharacter* TargetCharacter);
	void OnHitReactMontageEnded(UAnimMontage* Montage, bool bInterrupted, AEveEnemyBase* Enemy);
};
