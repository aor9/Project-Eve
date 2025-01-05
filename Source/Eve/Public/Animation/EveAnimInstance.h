// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EveAnimInstance.generated.h"

class AEveCharacter;
/**
 * 
 */
UCLASS()
class EVE_API UEveAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UEveAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, Category=Character, meta=(AllowPrivateAccess = "true"))
	AEveCharacter* EveCharacter;

	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	FVector ForwardVector;
	
	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	FVector RightVector;

	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	FVector2D MoveDirVector2D;

	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	FVector2D ForwardVector2D;

	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	FVector2D RightVector2D;

	UPROPERTY(BlueprintReadOnly, Category=Movemnt, meta=(AllowPrivateAccess = "true"))
	float ForwardDot;

	UPROPERTY(BlueprintReadOnly, Category=Movemnt, meta=(AllowPrivateAccess = "true"))
	float RightDot;
	
	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	bool bShouldMove = false;
	
};
