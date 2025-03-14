// Copyright aor9


#include "Character/EveCharacter.h"

#include "AbilitySystemComponent.h"
#include "Eve.h"
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
#include "Components/PlayerCombatComponent.h"

#include "EveDebugHelper.h"
#include "Components/WidgetComponent.h"
#include "Game/EveGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/EveUserWidget.h"


AEveCharacter::AEveCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 700.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));

	StaminaBar = CreateDefaultSubobject<UWidgetComponent>("StaminaBar");
	StaminaBar->SetupAttachment(Camera);
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
		NiagaraSnowComponent->SetFloatParameter(FName("WindPower"), -150.f);
		NiagaraSnowComponent->SetFloatParameter(FName("SnowRate"), 450.f);	
	}

	Tags.Emplace(ACTOR_TAG_PLAYER);
}

void AEveCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// ** Snow Effect
	if (NiagaraSnowComponent && Camera)
	{
		FVector CameraLocation = Camera->GetComponentLocation();
		NiagaraSnowComponent->SetWorldLocation(CameraLocation + FVector(0.f, 0.f, 300.f));
	}

	// ** Character Rotation
	FRotator CurrentRotation = GetActorRotation();
	FRotator SmoothedRotation = FMath::RInterpTo(CurrentRotation, NewRotation, DeltaSeconds, 20.0f);
	SetActorRotation(SmoothedRotation);
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
	YawRotation = FMath::Atan2(MouseNormal.Y, MouseNormal.X) * (180.0f / PI);
	NewRotation = FRotator(0.0f, YawRotation, 0.0f);
	
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
	InitMapEffect();

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AEveCharacter::InitStaminaWidget);
}

// ** 맵 진입시 초기 적용할 Gamepaly Effect 적용 (체온, 배고픔)
void AEveCharacter::InitMapEffect() const
{
	AEveGameModeBase* GameMode = Cast<AEveGameModeBase>(UGameplayStatics::GetGameMode(this));
	
	if (GameMode && GameMode->TemperatureEffect && GameMode->HungerEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		FGameplayEffectSpecHandle TempSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameMode->TemperatureEffect, 1.0f, EffectContext);
		if (TempSpecHandle.IsValid())
		{
			FGameplayEffectSpec* TempSpec = TempSpecHandle.Data.Get();
			if (TempSpec)
			{
				FScalableFloat TemperatureEffectMagnitude = GameMode->TemperatureEffectMagnitude;
				float ColdMagnitude = TemperatureEffectMagnitude.GetValue();
				TempSpec->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Attributes.Vital.BodyTemperature")), ColdMagnitude);
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*TempSpec);
			}
		}
		
		FGameplayEffectSpecHandle HungerSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameMode->HungerEffect, 1.0f, EffectContext);
		if (HungerSpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*HungerSpecHandle.Data.Get());
		}

		FGameplayEffectSpecHandle StaminaSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameMode->StaminaEffect, 1.0f, EffectContext);
		if (StaminaSpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*StaminaSpecHandle.Data.Get());
		}
	}
}

void AEveCharacter::InitStaminaWidget()
{
	if(UEveUserWidget* EveUserWidget = Cast<UEveUserWidget>(StaminaBar->GetUserWidgetObject()))
	{
		EveUserWidget->InitWidgetController(this);
	}

	if(const UEveAttributeSet* EveAS = Cast<UEveAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			EveAS->GetStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnStaminaChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			EveAS->GetMaxStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnMaxStaminaChanged.Broadcast(Data.NewValue);
			}
		);

		OnStaminaChanged.Broadcast(EveAS->GetStamina());
		OnMaxStaminaChanged.Broadcast(EveAS->GetMaxStamina());
	}
}
