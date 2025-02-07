// Copyright aor9

#pragma once

#include "EveStructTypes.generated.h"

class UEvePlayerLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FEvePlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEvePlayerLinkedAnimLayer> WeaponAnimLayerToLink;
};