// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "EveTypes/EveStructTypes.h"
#include "Items/Weapons/EveWeaponBase.h"
#include "EvePlayerWeapon.generated.h"

class USphereComponent;
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

protected:

private:
};
