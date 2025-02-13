// Copyright aor9


#include "AbilitySystem/Abilities/EvePlayerRolling.h"

#include "EveDebugHelper.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/EveCharacter.h"
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
	
	EveCharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Player.State.Rolling")));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
