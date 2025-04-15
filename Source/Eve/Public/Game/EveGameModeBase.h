// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "ScalableFloat.h"
#include "GameFramework/GameModeBase.h"
#include "EveGameModeBase.generated.h"

class UGameplayEffect;
class UCharacterClassInfo;
/**
 * 
 */

USTRUCT(Blueprintable)
struct FEnvironmentStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	FScalableFloat TemperatureEffectMagnitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	float WindStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	float SnowRate;
};

UCLASS()
class EVE_API AEveGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Environment")
	TSubclassOf<UGameplayEffect> TemperatureEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Environment")
	TSubclassOf<UGameplayEffect> HungerEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Environment")
	TSubclassOf<UGameplayEffect> StaminaEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Environment")
	FEnvironmentStruct EnvironmentStruct;
};
