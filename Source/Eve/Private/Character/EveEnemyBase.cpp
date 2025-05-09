// Copyright aor9


#include "Character/EveEnemyBase.h"

#include "AbilitySystemComponent.h"
#include "Eve.h"
#include "EveDebugHelper.h"
#include "AbilitySystem/EveAbilitySystemComponent.h"
#include "AbilitySystem/EveAbilitySystemLibrary.h"
#include "AI/EveAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/EnemyCombatComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widgets/EveUserWidget.h"
#include "MotionWarpingComponent.h"
#include "Components/CapsuleComponent.h"

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

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");
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

void AEveEnemyBase::InitDefaultAttributes() const
{
	UEveAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void AEveEnemyBase::Die()
{
	AbilitySystemComponent->ClearAllAbilities();
	
	USkeletalMeshComponent* EnemyMesh = GetMesh();

	EnemyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	EnemyMesh->SetCollisionObjectType(ECC_Pawn);
	EnemyMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	EnemyMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	SetLifeSpan(15.f);
	Super::Die();
}

void AEveEnemyBase::SetCombatTarget(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AEveEnemyBase::GetCombatTarget() const
{
	return CombatTarget;
}


void AEveEnemyBase::GiveStartupAbilities() const
{
	UEveAbilitySystemComponent* EveASC = CastChecked<UEveAbilitySystemComponent>(AbilitySystemComponent);
	EveASC->AddCharacterAbilities(StartupAbilities);
}
