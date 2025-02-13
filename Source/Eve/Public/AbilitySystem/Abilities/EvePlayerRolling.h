// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/EvePlayerGameplayAbility.h"
#include "Components/TimelineComponent.h"
#include "EvePlayerRolling.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API UEvePlayerRolling : public UEvePlayerGameplayAbility
{
	GENERATED_BODY()

public:
	float RollingPower = 500.f;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UFUNCTION()
	void OnRollingComplete();

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* RollMontage;

};
