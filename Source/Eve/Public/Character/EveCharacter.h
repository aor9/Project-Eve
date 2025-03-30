// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Character/EveCharacterBase.h"
#include "Interfaces/InteractionInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EveCharacter.generated.h"

class USphereComponent;
class UDataAsset_InputConfig;
class UNiagaraComponent;
class UNiagaraSystem;
class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
class AController;
class UPlayerCombatComponent;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class EVE_API AEveCharacter : public AEveCharacterBase
{
	GENERATED_BODY()
public:
	AEveCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	void RotateToMouseDirection(const FVector2D& MouseNormal);

	UPROPERTY(EditAnywhere, Category = "Snowing")
	UNiagaraSystem* SnowingEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Snowing")
	UNiagaraComponent* NiagaraSnowComponent = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnStaminaChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxStaminaChanged;
	
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TSet<AActor*> TargetInteractions;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> StaminaBar;

private:
	virtual void InitAbilityActorInfo() override;

	void InitMapEffect() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess= "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess= "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
	USphereComponent* InteractionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess= "true", DisplayPriority = 1))
	UPlayerCombatComponent* PlayerCombatComponent;

	float YawRotation;
	FRotator NewRotation;

	void InitStaminaWidget();

public:
	FORCEINLINE UPlayerCombatComponent* GetPlayerCombatComponent() const { return PlayerCombatComponent; }
};
