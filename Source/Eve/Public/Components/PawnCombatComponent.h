// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AEveWeaponBase;
/**
 * 
 */
UCLASS()
class EVE_API UPawnCombatComponent : public UPawnComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	void RegisterSpawnedWeapon(FGameplayTag WeaponTagToRegister, AEveWeaponBase* WeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	AEveWeaponBase* GetCarriedWeaponByTag(FGameplayTag WeaponTag) const;

	UPROPERTY(BlueprintReadWrite, Category = "Player|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	AEveWeaponBase* GetCurrentEquippedWeapon() const;
	 
	
private:
	UPROPERTY()
	TMap<FGameplayTag, AEveWeaponBase*> CarriedWeaponMap;
	
};
