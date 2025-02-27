// Copyright aor9


#include "AnimNotify/MeleeHitCheck.h"

#include "EveDebugHelper.h"
#include "Character/EveCharacter.h"
#include "Components/PlayerCombatComponent.h"


void UMeleeHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(AEveCharacter* Character = Cast<AEveCharacter>(MeshComp->GetOwner()))
	{
		UAbilitySystemComponent* OwnerASC = Character->GetAbilitySystemComponent();
		FGameplayEffectSpecHandle SpecHandle = OwnerASC->MakeOutgoingSpec(DamageEffectClass, 1, OwnerASC->MakeEffectContext());
		Character->GetPlayerCombatComponent()->MeleeAttackTrace(SpecHandle);
	}
}
