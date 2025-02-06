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
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Roll(const FInputActionValue& InputValue);
	void GetMouseNormal();
	
private:
	UPROPERTY()
	APawn* ControlledPawn;

	UPROPERTY()
	UEveBaseAnimInstance* EveAnimInstance;

	UPROPERTY()
	AEveCharacter* EveCharacter;
	
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	FVector LastMoveDirection;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UEveInputData> InputData;

	UPROPERTY()
	TObjectPtr<UEveAbilitySystemComponent> EveAbilitySystemComponent;

	UEveAbilitySystemComponent* InitASC();
};
