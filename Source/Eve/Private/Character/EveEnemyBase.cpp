// Copyright aor9


#include "Character/EveEnemyBase.h"

#include "AbilitySystemComponent.h"
#include "Eve.h"
#include "EveDebugHelper.h"
#include "AbilitySystem/EveAbilitySystemComponent.h"
#include "AI/EveAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/EnemyCombatComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widgets/EveUserWidget.h"


AEveEnemyBase::AEveEnemyBase()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;

	AbilitySystemComponent = CreateDefaultSubobject<UEveAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UEveAttributeSet>("AttributeSet");

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("UEnemyCombatComponent");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AEveEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	EveAIController = Cast<AEveAIController>(NewController);
	EveAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	EveAIController->RunBehaviorTree(BehaviorTree);
	EveAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	EveAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);
}

void AEveEnemyBase::SetHitReacting(bool bReacting)
{
	EveAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bReacting);
}

void AEveEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	GiveStartupAbilities();

	if(UEveUserWidget* EveUserWidget = Cast<UEveUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		EveUserWidget->InitWidgetController(this);
	}
	
	if(const UEveAttributeSet* EveAS = Cast<UEveAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EveAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
			);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EveAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
			);

		OnHealthChanged.Broadcast(EveAS->GetHealth());
		OnMaxHealthChanged.Broadcast(EveAS->GetMaxHealth());
	}

	Tags.Emplace(ACTOR_TAG_ENEMY);
}

void AEveEnemyBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UEveAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitDefaultAttributes();
}

void AEveEnemyBase::Die()
{
	SetLifeSpan(15.f);
	Super::Die();
}

void AEveEnemyBase::GiveStartupAbilities() const
{
	UEveAbilitySystemComponent* EveASC = CastChecked<UEveAbilitySystemComponent>(AbilitySystemComponent);
	EveASC->AddEnemyAbilities(StartupAbilities);
}
