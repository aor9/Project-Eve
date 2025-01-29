// Copyright aor9


#include "Character/EveCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "EveDebugHelper.h"
#include "AbilitySystem/EveAbilitySystemComponent.h"


AEveCharacterBase::AEveCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
}

UAbilitySystemComponent* AEveCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AEveCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEveCharacterBase::InitAbilityActorInfo()
{
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

void AEveCharacterBase::AddCharacterAbilities()
{
	if(!HasAuthority())	return;

	UEveAbilitySystemComponent* EveASC = CastChecked<UEveAbilitySystemComponent>(AbilitySystemComponent);
	EveASC->AddCharacterAbilities(StartupAbilities);
	Debug::Print("Character Abilities Granted");
}
