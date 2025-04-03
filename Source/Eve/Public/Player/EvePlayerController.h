// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "EvePlayerController.generated.h"

class UEveInputData;
class AEveCharacter;
class UEveBaseAnimInstance;
struct FInputActionValue;
class UEveAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class EVE_API AEvePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AEvePlayerController(const FObjectInitializer& ObjectInitializer);
	void StartRolling(FVector Direction, float RollingPower);
	void UpdateInteractionWidget() const;

	FVector LastMoveDirection;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private:
	UEveAbilitySystemComponent* InitASC();
	
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Lmb(const FInputActionValue& InputValue);
	void GetMouseNormal();
	void DetectInteractableUnderCursor();
	void RemoveInteractionTagSafely();
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY()
	APawn* ControlledPawn;

	UPROPERTY()
	UEveBaseAnimInstance* EveAnimInstance;

	UPROPERTY()
	AEveCharacter* EveCharacter;
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UEveInputData> InputData;

	UPROPERTY()
	TObjectPtr<UEveAbilitySystemComponent> EveAbilitySystemComponent;

	UPROPERTY()
	AActor* CurrentInteractable = nullptr;

	FVector2D CachedMouseNormal;
	
	bool bInteract = false;
	
	FVector RollingDirection;
	float RollingPower;

public:
	UEveBaseAnimInstance* GetEveBaseAnimInstance() const { return EveAnimInstance; }
};
