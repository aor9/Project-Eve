// Copyright aor9


#include "Character/EveCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "EveDebugHelper.h"
#include "AbilitySystem/EveAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"


AEveCharacterBase::AEveCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->bReceivesDecals = false;
}

UAbilitySystemComponent* AEveCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* AEveCharacterBase::GetHitReactMontage()
{
	return HitReactMontage;
}

void AEveCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEveCharacterBase::InitAbilityActorInfo()
{
}

void AEveCharacterBase::Die()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEveCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultPrimaryAttributes);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AEveCharacterBase::InitDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AEveCharacterBase::AddCharacterAbilities() const
{
	if(!HasAuthority())	return;

	UEveAbilitySystemComponent* EveASC = CastChecked<UEveAbilitySystemComponent>(AbilitySystemComponent);
	EveASC->AddCharacterAbilities(StartupAbilities);
}
