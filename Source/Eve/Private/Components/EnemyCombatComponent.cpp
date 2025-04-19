// Copyright aor9


#include "Components/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Character/EveCharacter.h"
#include "Engine/OverlapResult.h"


void UEnemyCombatComponent::MeleeAttackTrace(FGameplayEffectSpecHandle DamageSpecHandle, bool bIsBoss)
{
	AActor* Owner = GetOwner();
	if(!Owner)	return;

	// todo: Boss 는 Hit Collider 기반으로 수정하는게 좋을 것 같다고 생각합니다.
	FVector Start = Owner->GetActorLocation();
	FVector End;
	FCollisionShape AttackShape;
	if(bIsBoss)
	{
		End = Start + Owner->GetActorForwardVector() * 250.f;
		AttackShape = FCollisionShape::MakeSphere(150.0f);
	}
	else
	{
		End = Start + Owner->GetActorForwardVector() * 80.f;
		AttackShape = FCollisionShape::MakeSphere(50.0f);
	}

	TArray<FOverlapResult> HitResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);
	
	bool bHit = GetWorld()->OverlapMultiByChannel(HitResults, End,FQuat::Identity,ECC_Pawn, AttackShape, Params);
	
	if (bHit)
	{
		for (const FOverlapResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();

			if (!HitActor || HitActor->ActorHasTag("Enemy")) continue;

			if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor))
			{
				TargetASC->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());
				AEveCharacter* EveCharacter = Cast<AEveCharacter>(Hit.GetActor());
				if (UEveAttributeSet* TargetAttributes = Cast<UEveAttributeSet>(EveCharacter->GetAttributeSet()))
				{
					float CurrentHealth = TargetAttributes->GetHealth();
					if (CurrentHealth <= 0.f)
					{
						EveCharacter->Die();
					}
				}
			}
		}
	}
}
