// Copyright aor9


#include "AbilitySystem/Abilities/EvePlayerRolling.h"

#include "Eve.h"
#include "EveDebugHelper.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/EveCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Player/EvePlayerController.h"


void UEvePlayerRolling::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AEvePlayerController* EvePlayerController = GetPlayerControllerFromActorInfo();
	AEveCharacter* EveCharacter = GetPlayerCharacterFromActorInfo();
	
	if(!EveCharacter || !RollMontage)	return;

	FVector RollDirection = EvePlayerController->LastMoveDirection.GetSafeNormal();
		
	UAnimInstance* AnimInstance = EveCharacter->GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		// **Collision
		EveCharacter->GetCapsuleComponent()->SetCollisionProfileName(FName("Rolling"));
		
		// ** Stamina 감소
		UAbilitySystemComponent* ASC = EveCharacter->GetAbilitySystemComponent();
		const UEveAttributeSet* EveAS = Cast<UEveAttributeSet>(EveCharacter->GetAttributeSet());
		if (!EveAS) return;

		float CurrentStamina = EveAS->GetStamina();
		const float StaminaCost = 0.33f;
		
		if (CurrentStamina < StaminaCost)
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
			return;
		}

		ASC->ApplyModToAttribute(UEveAttributeSet::GetStaminaAttribute(), EGameplayModOp::Additive, -StaminaCost);

		// ** Rolling 실행
		EveCharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Player.State.Rolling")));
		
		AnimInstance->Montage_Play(RollMontage);
		UAbilityTask_PlayMontageAndWait* RollingTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, RollMontage, 1.0f, NAME_None);
		EvePlayerController->StartRolling(RollDirection, RollingPower);
		
		RollingTask->OnCompleted.AddDynamic(this, &UEvePlayerRolling::OnRollingComplete);
		RollingTask->ReadyForActivation();
	}
}

void UEvePlayerRolling::OnRollingComplete()
{
	AEveCharacter* EveCharacter = GetPlayerCharacterFromActorInfo();
	UAbilitySystemComponent* ASC = EveCharacter->GetAbilitySystemComponent();
	
	if(!EveCharacter || !ASC)	return;
	
	EveCharacter->GetCapsuleComponent()->SetCollisionProfileName(FName("Pawn"));
	EveCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	EveCharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Player.State.Rolling")));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
