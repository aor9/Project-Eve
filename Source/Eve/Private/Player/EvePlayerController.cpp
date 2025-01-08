// Copyright aor9


#include "Player/EvePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "System/EveAssetManager.h"
#include "EveGameplayTags.h"
#include "Animation/EveAnimInstance.h"
#include "Character/EveCharacter.h"
#include "Data/EveInputData.h"
#include "Kismet/KismetMathLibrary.h"


AEvePlayerController::AEvePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bReplicates = true;
}

void AEvePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (const UEveInputData* InputData = UEveAssetManager::GetAssetByName<UEveInputData>("InputData"))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
		}
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AEvePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetMouseNormal();
	
	if(ControlledPawn && EveAnimInstance->bIsRolling)
	{
		LastMoveDirection.Normalize();
		ControlledPawn->AddMovementInput(LastMoveDirection, 500.f * DeltaTime);

		FRotator TargetRotation = LastMoveDirection.Rotation();
		ControlledPawn->SetActorRotation(TargetRotation);
	}
}

void AEvePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (const UEveInputData* InputData = UEveAssetManager::GetAssetByName<UEveInputData>("InputData"))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		auto MoveAction = InputData->FindInputActionByTag(EveGameplayTags::Input_Action_Move);
		auto RollAction = InputData->FindInputActionByTag(EveGameplayTags::Input_Action_Roll);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Roll);
	}
}

void AEvePlayerController::Input_Move(const FInputActionValue& InputValue)
{
	const FVector2D InputAxisVector = InputValue.Get<FVector2D>();

	if(ControlledPawn == nullptr)
	{
		ControlledPawn = GetPawn();
	}
	if (!ControlledPawn) return;

	AEveCharacter* EveCharacter = Cast<AEveCharacter>(ControlledPawn);
	if (!EveCharacter) return;

	if(EveAnimInstance == nullptr)
	{
		EveAnimInstance = Cast<UEveAnimInstance>(EveCharacter->GetMesh()->GetAnimInstance());
	}
	if (!EveAnimInstance) return;

	if(EveAnimInstance->bIsRolling == true)	return;
	
	const FVector ForwardDirection = FVector(1.0f, 0.0f, 0.0f);
	const FVector RightDirection = FVector(0.0f, -1.0f, 0.0f);
	const FVector MoveDirection = (ForwardDirection * InputAxisVector.X) + (RightDirection * InputAxisVector.Y);
	LastMoveDirection = MoveDirection.GetSafeNormal();
	
	ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.X);
	ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.Y);
}

void AEvePlayerController::Input_Roll(const FInputActionValue& InputValue)
{
	if (ControlledPawn == nullptr)
	{
		ControlledPawn = GetPawn();
	}
	if (!ControlledPawn) return;

	AEveCharacter* EveCharacter = Cast<AEveCharacter>(ControlledPawn);
	if (!EveCharacter) return;

	if(EveAnimInstance == nullptr)
	{
		EveAnimInstance = Cast<UEveAnimInstance>(EveCharacter->GetMesh()->GetAnimInstance());
	}
	if (!EveAnimInstance) return;
	
	if(EveAnimInstance->bIsRolling == true)	return;
	
	EveAnimInstance->bIsRolling = true;
}


void AEvePlayerController::GetMouseNormal()
{
	if (!EveAnimInstance)	return;
	
	if (EveAnimInstance->bIsRolling)	return;
	
	FVector2D MousePosition;

	if (GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		GetViewportSize(ViewportSizeX, ViewportSizeY);
		FVector2D ScreenCenter = FVector2D(ViewportSizeX * 0.5f, ViewportSizeY * 0.5f);
		FVector2D MouseDelta = MousePosition - ScreenCenter;
		FVector2D MouseNormalFromCenter = MouseDelta.GetSafeNormal();

		if (AEveCharacter* ControlledCharacter = Cast<AEveCharacter>(GetPawn()))
		{
			ControlledCharacter->RotateToMouseDirection(MouseNormalFromCenter);
		}
	}
}
