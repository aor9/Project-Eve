// Copyright aor9


#include "Items/Weapons/EveWeaponBase.h"

#include "Components/BoxComponent.h"

AEveWeaponBase::AEveWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
}
