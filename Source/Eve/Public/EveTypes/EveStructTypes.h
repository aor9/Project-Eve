// Copyright aor9

#pragma once

#include "EveStructTypes.generated.h"

class UEveGameplayAbility;
class UEvePlayerLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FEvePlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEvePlayerLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UEveGameplayAbility> DefaultWeaponAbilities;
};