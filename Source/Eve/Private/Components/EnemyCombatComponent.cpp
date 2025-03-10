// Copyright aor9


#include "Components/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


void UEnemyCombatComponent::MeleeAttackTrace(FGameplayEffectSpecHandle DamageSpecHandle)
{
	AActor* Owner = GetOwner();
	if(!Owner)	return;

	FVector Start = Owner->GetActorLocation();
	FVector End = Start + Owner->GetActorForwardVector() * 80.f;

	TArray<FHitResult> HitResults;
	FCollisionShape AttackShape = FCollisionShape::MakeSphere(50.0f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);
	
	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Pawn, AttackShape, Params);

	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			if(Hit.GetActor()->ActorHasTag("Enemy"))	continue;
			
			if(UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Hit.GetActor()))
			{
				TargetASC->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());	
			}
		}
	}
}
