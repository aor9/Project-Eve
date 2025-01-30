// Copyright aor9


#include "Character/EveCharacter.h"

#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/EveAbilitySystemComponent.h"
#include "AbilitySystem/EveAttributeSet.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/EvePlayerController.h"
#include "Player/EvePlayerState.h"
#include "UI/HUD/EveHUD.h"

#include "EveDebugHelper.h"


AEveCharacter::AEveCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 700.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
}

void AEveCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	NiagaraSnowComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
		SnowingEffect,
		SpringArm,
		NAME_None,
		FVector(0.f, -50.f, 0.f),
		FRotator::ZeroRotator,
		EAttachLocation::Type::KeepWorldPosition,
		true
		);
	
	if(NiagaraSnowComponent)
	{
		// TODO : 날씨를 조절하는 클래스에서 바람 세기, 눈이 얼마나 내리는지 등 가져오기
		NiagaraSnowComponent->SetFloatParameter(FName("WindPower"), -100.f);
		NiagaraSnowComponent->SetFloatParameter(FName("SnowRate"), 300.f);	
	}
}

void AEveCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (NiagaraSnowComponent && Camera)
	{
		FVector CameraLocation = Camera->GetComponentLocation();
		NiagaraSnowComponent->SetWorldLocation(CameraLocation + FVector(0.f, 0.f, 300.f));
	}
}


void AEveCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// init ability info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
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
	Cast<UEveAbilitySystemComponent>(EvePlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	
	AbilitySystemComponent = EvePlayerState->GetAbilitySystemComponent();
	AttributeSet = EvePlayerState->GetAttributeSet();

	if(AEvePlayerController* EvePlayerController = Cast<AEvePlayerController>(GetController()))
	{
		if(AEveHUD* EveHUD = Cast<AEveHUD>(EvePlayerController->GetHUD()))
		{
			EveHUD->InitOverlay(EvePlayerController, EvePlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitDefaultAttributes();
}
