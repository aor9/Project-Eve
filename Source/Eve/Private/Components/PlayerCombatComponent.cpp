// Copyright aor9


#include "Components/PlayerCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EveDebugHelper.h"
#include "Character/EveCharacter.h"
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
	FVector End = Start + Owner->GetActorForwardVector() * 100.f;

	TArray<FHitResult> HitResults;
	FCollisionShape AttackShape = FCollisionShape::MakeSphere(75.0f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);
	
	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Pawn, AttackShape, Params);

	if (bHit)
	{
		PlayCombatCameraShake();
		for (const FHitResult& Hit : HitResults)
		{
			if(ACharacter* TargetCharacter = Cast<ACharacter>(Hit.GetActor()))
			{
				PlayHitReact(TargetCharacter);
			}
			
			if(UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Hit.GetActor()))
			{
				TargetASC->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());	
			}
		}
	}
}

void UPlayerCombatComponent::PlayCombatCameraShake() const
{
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
		if (AEveCharacterBase* EveCharacter = Cast<AEveCharacterBase>(TargetCharacter))
		{
			if (UAnimMontage* HitReactMontage = EveCharacter->GetHitReactMontage())
			{
				AnimInstance->Montage_Play(HitReactMontage);
			}
		}
	}
}
