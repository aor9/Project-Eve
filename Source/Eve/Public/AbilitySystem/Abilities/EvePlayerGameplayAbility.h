// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/EveGameplayAbility.h"
#include "Components/PlayerCombatComponent.h"
#include "EvePlayerGameplayAbility.generated.h"

class AEvePlayerController;
class AEveCharacter;
/**
 * 
 */
UCLASS()
class EVE_API UEvePlayerGameplayAbility : public UEveGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	AEveCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure)
	AEvePlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure)
	UPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AEveCharacter> CachedEvePlayerCharacter;
	TWeakObjectPtr<AEvePlayerController> CachedEvePlayerController;
	
};
