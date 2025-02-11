// Copyright aor9


#include "Player/EvePlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EveDebugHelper.h"
#include "System/EveAssetManager.h"
#include "EveGameplayTags.h"
#include "AbilitySystem/EveAbilitySystemComponent.h"
#include "Animation/EveBaseAnimInstance.h"
#include "Character/EveCharacter.h"
#include "DataAssets/Input/EveInputData.h"
#include "Input/EveInputComponent.h"
#include "Kismet/KismetMathLibrary.h"


AEvePlayerController::AEvePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bReplicates = true;
}

void AEvePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	ControlledPawn = GetPawn();
	EveCharacter = Cast<AEveCharacter>(ControlledPawn);
	if (EveCharacter)
	{
		EveAnimInstance = Cast<UEveBaseAnimInstance>(EveCharacter->GetMesh()->GetAnimInstance());
	}

	InputData = UEveAssetManager::GetAssetByName<UEveInputData>("InputData");
	if (InputData)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
		}
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AEvePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	GetMouseNormal();
}

void AEvePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputData = UEveAssetManager::GetAssetByName<UEveInputData>("InputData");
	if(InputData)
	{
		UEveInputComponent* EveInputComponent = CastChecked<UEveInputComponent>(InputComponent);

		auto MoveAction = InputData->FindInputActionByTag(EveGameplayTags::Input_Action_Move);
		auto RollAction = InputData->FindInputActionByTag(EveGameplayTags::Input_Action_Roll);
		EveInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		EveInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Roll);

		EveInputComponent->BindAbilityActions(InputData, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	}
}

void AEvePlayerController::Input_Move(const FInputActionValue& InputValue)
{
	if (InitASC()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Player.State.NoMove"))))
	{
		return;
	}
	
	const FVector2D InputAxisVector = InputValue.Get<FVector2D>();
	
	if (!ControlledPawn || !EveCharacter || !EveAnimInstance) return;
	
	const FVector ForwardDirection = FVector(1.0f, 0.0f, 0.0f);
	const FVector RightDirection = FVector(0.0f, -1.0f, 0.0f);
	
	ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.X);
	ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.Y);
}

void AEvePlayerController::Input_Roll(const FInputActionValue& InputValue)
{
	if (!ControlledPawn || !EveCharacter || !EveAnimInstance) return;
	
	// if(EveAnimInstance->bIsRolling == true)	return;
	
	// EveAnimInstance->bIsRolling = true;
}


void AEvePlayerController::GetMouseNormal()
{
	FVector2D MousePosition;
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	if (GetMousePosition(MousePosition.X, MousePosition.Y) && !InitASC()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Player.State.NoMove"))))
	{
		FVector2D ScreenCenter = FVector2D(ViewportSizeX* 0.5f, ViewportSizeY * 0.5f);
		FVector2D MouseDelta = MousePosition - ScreenCenter;
		CachedMouseNormal = MouseDelta.GetSafeNormal();
		if (AEveCharacter* ControlledCharacter = Cast<AEveCharacter>(GetPawn()))
		{
			ControlledCharacter->RotateToMouseDirection(CachedMouseNormal);
		}
	}
	else
	{
		if (AEveCharacter* ControlledCharacter = Cast<AEveCharacter>(GetPawn()))
		{
			ControlledCharacter->RotateToMouseDirection(CachedMouseNormal);
		}
	}
}

void AEvePlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	
}

void AEvePlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(InitASC() == nullptr)	return;
	InitASC()->AbilityInputTagReleased(InputTag);
}

void AEvePlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(InitASC() == nullptr)	return;
	InitASC()->AbilityInputTagHeld(InputTag);
}

UEveAbilitySystemComponent* AEvePlayerController::InitASC()
{
	if(EveAbilitySystemComponent == nullptr)
	{
		EveAbilitySystemComponent = Cast<UEveAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return EveAbilitySystemComponent;
}
