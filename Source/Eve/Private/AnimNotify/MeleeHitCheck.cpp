// Copyright aor9


#include "AnimNotify/MeleeHitCheck.h"

#include "EveDebugHelper.h"
#include "Character/EveCharacter.h"
#include "Character/EveEnemyBase.h"
#include "Components/EnemyCombatComponent.h"
#include "Components/PlayerCombatComponent.h"


void UMeleeHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AEveCharacterBase* Character = Cast<AEveCharacterBase>(MeshComp->GetOwner()))
	{
		UAbilitySystemComponent* OwnerASC = Character->GetAbilitySystemComponent();
		FGameplayEffectSpecHandle SpecHandle = OwnerASC->MakeOutgoingSpec(DamageEffectClass, 1, OwnerASC->MakeEffectContext());

		if (AEveCharacter* PlayerCharacter = Cast<AEveCharacter>(Character))
		{
			UE_LOG(LogTemp, Log, TEXT("Melee Attack by Player"));
			PlayerCharacter->GetPlayerCombatComponent()->MeleeAttackTrace(SpecHandle);
		}
		else if (AEveEnemyBase* EnemyCharacter = Cast<AEveEnemyBase>(Character))
		{
			UE_LOG(LogTemp, Log, TEXT("Melee Attack by Enemy"));
			EnemyCharacter->GetEnemyCombatComponent()->MeleeAttackTrace(SpecHandle);
		}
	}
}
