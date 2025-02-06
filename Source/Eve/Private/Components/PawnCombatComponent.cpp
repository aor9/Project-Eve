// Copyright aor9


#include "Components/PawnCombatComponent.h"

#include "EveDebugHelper.h"
#include "Items/Weapons/EveWeaponBase.h"


void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTagToRegister, AEveWeaponBase* WeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CarriedWeaponMap.Contains(WeaponTagToRegister), TEXT("%s has already been added as carried weapon"), *WeaponTagToRegister.ToString());
	check(WeaponToRegister);

	CarriedWeaponMap.Emplace(WeaponTagToRegister, WeaponToRegister);

	if(bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = WeaponTagToRegister;
	}

	const FString WeaponString = FString::Printf(TEXT("A weapon name : %s has been registered using the tag %s"), *WeaponToRegister->GetName(), *WeaponTagToRegister.ToString());
	Debug::Print(WeaponString);
}

AEveWeaponBase* UPawnCombatComponent::GetCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	if(CarriedWeaponMap.Contains(WeaponTag))
	{
		if(AEveWeaponBase* const* FoundWeapon = CarriedWeaponMap.Find(WeaponTag))
		{
			return *FoundWeapon;
		}
	}
	
	return nullptr;
}

AEveWeaponBase* UPawnCombatComponent::GetCurrentEquippedWeapon() const
{
	if(!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
