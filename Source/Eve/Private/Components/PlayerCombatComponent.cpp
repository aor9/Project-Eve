// Copyright aor9


#include "Components/PlayerCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EveDebugHelper.h"
#include "AI/EveAIController.h"
#include "Character/EveCharacter.h"
#include "Character/EveEnemyBase.h"
#include "Items/Weapons/EvePlayerWeapon.h"
#include "Kismet/GameplayStatics.h"


AEvePlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	return Cast<AEvePlayerWeapon>(GetCarriedWeaponByTag(WeaponTag));
}

void UPlayerCombatComponent::MeleeAttackTrace(FGameplayEffectSpecHandle DamageSpecHandle)
{
	AActor* Owner = GetOwner();
	if(!Owner)	return;

	FVector Start = Owner->GetActorLocation();
	// TODO: melee attack의 범위도 하드코딩 수정
	FVector End = Start + Owner->GetActorForwardVector() * 80.f;

	TArray<FHitResult> HitResults;
	FCollisionShape AttackShape = FCollisionShape::MakeSphere(55.0f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);
	
	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Pawn, AttackShape, Params);

	if (bHit)
	{
		PlayCombatCameraShake();
		for (const FHitResult& Hit : HitResults)
		{
			AEveEnemyBase* TargetEnemy = Cast<AEveEnemyBase>(Hit.GetActor());
			if(TargetEnemy)
			{
				PlayHitReact(TargetEnemy);
			}

			// Todo : damage 클래스 분리
			if(UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Hit.GetActor()))
			{
				TargetASC->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());

				if (UEveAttributeSet* TargetAttributes = Cast<UEveAttributeSet>(TargetEnemy->GetAttributeSet()))
				{
					float CurrentHealth = TargetAttributes->GetHealth();
					if (CurrentHealth <= 0.f)
					{
						TargetEnemy->Die();
					}
				}
			}
		}
	}
}

void UPlayerCombatComponent::PlayCombatCameraShake() const
{
	// TODO: CameraShake 분리
	
	if (CombatCameraShake)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->ClientStartCameraShake(CombatCameraShake);
		}
	}
}

void UPlayerCombatComponent::PlayHitReact(ACharacter* TargetCharacter)
{
	if (TargetCharacter == nullptr) return;

	if (UAnimInstance* AnimInstance = TargetCharacter->GetMesh()->GetAnimInstance())
	{
		if (AEveEnemyBase* Enemy = Cast<AEveEnemyBase>(TargetCharacter))
		{
			if (UAnimMontage* HitReactMontage = Enemy->GetHitReactMontage())
			{
				AnimInstance->Montage_Play(HitReactMontage);

				// TODO: Hit React 관련 로직 분리 필요
				Enemy->SetHitReacting(true);
				FOnMontageEnded EndDelegate;
				EndDelegate.BindUObject(this, &UPlayerCombatComponent::OnHitReactMontageEnded, Enemy);
				AnimInstance->Montage_SetEndDelegate(EndDelegate, HitReactMontage);
			}
		}
	}
}

void UPlayerCombatComponent::OnHitReactMontageEnded(UAnimMontage* Montage, bool bInterrupted, AEveEnemyBase* Enemy)
{
	if(Enemy)
	{
		Enemy->SetHitReacting(false);
	}
}
