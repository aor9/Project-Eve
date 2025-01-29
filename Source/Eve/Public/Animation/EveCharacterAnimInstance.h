// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Animation/EveBaseAnimInstance.h"
#include "EveCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AEveCharacterBase;
/**
 * 
 */
UCLASS()
class EVE_API UEveCharacterAnimInstance : public UEveBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY()
	AEveCharacterBase* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bHasAcceleration;
};
