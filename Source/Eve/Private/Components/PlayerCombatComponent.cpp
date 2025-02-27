// Copyright aor9


#include "Components/PlayerCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EveDebugHelper.h"
#include "Character/EveCharacter.h"
#include "Items/Weapons/EvePlayerWeapon.h"


AEvePlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	return Cast<AEvePlayerWeapon>(GetCarriedWeaponByTag(WeaponTag));
}

void UPlayerCombatComponent::MeleeAttackTrace(FGameplayEffectSpecHandle DamageEffectSpecHandle)
{
	AActor* Owner = GetOwner();
	if(!Owner)	return;

	FVector Start = Owner->GetActorLocation();
	// todo: melee attack의 범위도 하드코딩 수정
	FVector End = Start + Owner->GetActorForwardVector() * 100.f;

	TArray<FHitResult> HitResults;
	FCollisionShape AttackShape = FCollisionShape::MakeSphere(75.0f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);
	
	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Pawn, AttackShape, Params);

	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			if(UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Hit.GetActor()))
			{
				TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());	
			}
		}
	}
}
