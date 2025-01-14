// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Character/EveCharacterBase.h"
#include "EveCharacter.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class USpringArmComponent;
class UCameraComponent;
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
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	void RotateToMouseDirection(const FVector2D& MouseNormal);

	UPROPERTY(EditAnywhere, Category = "Snowing")
	UNiagaraSystem* SnowingEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Snowing")
	UNiagaraComponent* NiagaraSnowComponent = nullptr;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;

private:
	void InitAbilityActorInfo();
};
