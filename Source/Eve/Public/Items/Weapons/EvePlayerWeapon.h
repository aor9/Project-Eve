// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "EveTypes/EveStructTypes.h"
#include "Items/Weapons/EveWeaponBase.h"
#include "EvePlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API AEvePlayerWeapon : public AEveWeaponBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FEvePlayerWeaponData PlayerWeaponData;
	
	
};
