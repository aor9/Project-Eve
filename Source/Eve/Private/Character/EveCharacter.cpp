// Copyright aor9


#include "Character/EveCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/EvePlayerState.h"


AEveCharacter::AEveCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 700.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
}

void AEveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEveCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// init ability info for the server
	InitAbilityActorInfo();
}

void AEveCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// init ability info for the client
	InitAbilityActorInfo();
}

void AEveCharacter::RotateToMouseDirection(const FVector2D& MouseNormal)
{
	float YawRotation = FMath::Atan2(MouseNormal.Y, MouseNormal.X) * (180.0f / PI);
	FRotator NewRotation = FRotator(0.0f, YawRotation, 0.0f);
	
	SetActorRotation(NewRotation);
}

void AEveCharacter::InitAbilityActorInfo()
{
	AEvePlayerState* EvePlayerState = GetPlayerState<AEvePlayerState>();
	check(EvePlayerState);
	EvePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(EvePlayerState, this);
	AbilitySystemComponent = EvePlayerState->GetAbilitySystemComponent();
	AttributeSet = EvePlayerState->GetAttributeSet();
}
