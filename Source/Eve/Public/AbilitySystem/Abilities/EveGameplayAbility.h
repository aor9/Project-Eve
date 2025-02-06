// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/EveAbilitySystemComponent.h"
#include "Components/PawnCombatComponent.h"
#include "EveGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API UEveGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Input")
	FGameplayTag StartInputTag;

	virtual FString GetDescription(int32 Level);

protected:
	float GetCooldown(float InLevel = 1.f) const;
	float GetStaminaCost(float InLevel = 1.f) const;

	UFUNCTION(BlueprintPure)
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure)
	UEveAbilitySystemComponent* GetASCFromActorInfo() const;
};
