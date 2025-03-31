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
	if (InitASC()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Player.State.Rolling"))) && ControlledPawn)
	{
		RollingDirection.Normalize();
		ControlledPawn->AddMovementInput(RollingDirection, RollingPower * DeltaTime);
		ControlledPawn->SetActorRotation(RollingDirection.Rotation());
	}
	else
	{
		GetMouseNormal();
	}
}

void AEvePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputData = UEveAssetManager::GetAssetByName<UEveInputData>("InputData");
	if(InputData)
	{
		UEveInputComponent* EveInputComponent = CastChecked<UEveInputComponent>(InputComponent);

		auto MoveAction = InputData->FindInputActionByTag(EveGameplayTags::Input_Action_Move);
		EveInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		
		auto LmbAction = InputData->FindInputActionByTag(EveGameplayTags::Input_LMB);
		EveInputComponent->BindAction(LmbAction, ETriggerEvent::Started, this, &ThisClass::Input_Lmb);

		EveInputComponent->BindAbilityActions(InputData, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	}
}

void AEvePlayerController::Input_Move(const FInputActionValue& InputValue)
{
	const FVector2D InputAxisVector = InputValue.Get<FVector2D>();
	const FVector ForwardDirection = FVector(1.0f, 0.0f, 0.0f);
	const FVector RightDirection = FVector(0.0f, -1.0f, 0.0f);
	const FVector MoveDirection = (ForwardDirection * InputAxisVector.X) + (RightDirection * InputAxisVector.Y);
	LastMoveDirection = MoveDirection.GetSafeNormal();
	
	if (InitASC()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Player.State.NoMove")))
		|| InitASC()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Player.State.Rolling"))))
	{
		return;
	}
	
	if (!ControlledPawn || !EveCharacter || !EveAnimInstance) return;
	
	ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.X);
	ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.Y);
}

void AEvePlayerController::Input_Lmb(const FInputActionValue& InputValue)
{
	if(bInteract && CurrentInteractable)
	{
		IInteractionInterface* InteractionActor = Cast<IInteractionInterface>(CurrentInteractable);
		InteractionActor->Interact(EveCharacter);
	}
}

void AEvePlayerController::StartRolling(FVector Direction, float RollPower)
{
	RollingDirection = Direction;
	RollingPower = RollPower;
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

		DetectInteractableUnderCursor();
		
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

void AEvePlayerController::DetectInteractableUnderCursor()
{
	FHitResult HitResult;
	if(GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		AActor* HitActor = HitResult.GetActor();
		if(HitActor)
		{
			IInteractionInterface* InteractionActor = Cast<IInteractionInterface>(HitActor);
			if(InteractionActor && EveCharacter->TargetInteractions.Find(HitActor))
			{
				bInteract = true;
				FGameplayTag InteractionTag = FGameplayTag::RequestGameplayTag(FName("Player.State.Interaction"));
				CurrentInteractable = HitActor;
				if (!InitASC()->HasMatchingGameplayTag(InteractionTag))
				{
					InitASC()->AddLooseGameplayTag(InteractionTag);
				}
			}
			else
			{
				bInteract = false;
				FGameplayTag InteractionTag = FGameplayTag::RequestGameplayTag(FName("Player.State.Interaction"));
				CurrentInteractable = nullptr;
				if (InitASC()->HasMatchingGameplayTag(InteractionTag))
				{
					InitASC()->RemoveLooseGameplayTag(InteractionTag);
				}
			}
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
