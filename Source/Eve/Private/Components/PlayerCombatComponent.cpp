// Copyright aor9


#include "Components/PlayerCombatComponent.h"

#include "Items/Weapons/EvePlayerWeapon.h"


AEvePlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	return Cast<AEvePlayerWeapon>(GetCarriedWeaponByTag(WeaponTag));
}
