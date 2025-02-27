// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "MeleeHitCheck.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class EVE_API UMeleeHitCheck : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
};
