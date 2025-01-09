// Copyright aor9


#include "Character/EveCharacterBase.h"


AEveCharacterBase::AEveCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

UAbilitySystemComponent* AEveCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AEveCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
