// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Animation/EveCharacterAnimInstance.h"
#include "EvePlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API UEvePlayerAnimInstance : public UEveCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData")
	AEveCharacter* OwningPlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bShouldEnterRelaxState;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 3.f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float ForwardDot;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float RightDot;

	float IdleElapsedTime;
	
	FVector ForwardVector;
	
	FVector RightVector;
	
	FVector2D MoveDirVector2D;
	
	FVector2D ForwardVector2D;
	
	FVector2D RightVector2D;
	
};
