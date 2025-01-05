// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EvePlayerController.generated.h"

struct FInputActionValue;

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
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

private:
	void Input_Move(const FInputActionValue& InputValue);
	void GetMouseNormal();
	
private:
	UPROPERTY()
	APawn* ControlledPawn;
	
	int32 ViewportSizeX;
	int32 ViewportSizeY;
};
