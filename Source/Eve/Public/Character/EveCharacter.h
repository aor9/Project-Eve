// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Character/EveCharacterBase.h"
#include "EveCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API AEveCharacter : public AEveCharacterBase
{
	GENERATED_BODY()
public:
	AEveCharacter();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void RotateToMouseDirection(const FVector2D& MouseNormal);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;
	
};
