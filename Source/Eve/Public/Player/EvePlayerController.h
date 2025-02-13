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

	FVector LastMoveDirection;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	APawn* ControlledPawn;

	UPROPERTY()
	UEveBaseAnimInstance* EveAnimInstance;

	UPROPERTY()
	AEveCharacter* EveCharacter;
	
	void Input_Move(const FInputActionValue& InputValue);

	FVector2D CachedMouseNormal;
	void GetMouseNormal();

	// ** Rolling
	FVector RollingDirection;
	float RollingPower;
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UEveInputData> InputData;

	UPROPERTY()
	TObjectPtr<UEveAbilitySystemComponent> EveAbilitySystemComponent;

	UEveAbilitySystemComponent* InitASC();

public:
	UEveBaseAnimInstance* GetEveBaseAnimInstance() const { return EveAnimInstance; }
};
