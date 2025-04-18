// Copyright aor9


#include "AbilitySystem/Abilities/EveProjectileSpawn.h"

#include "Actor/EveProjectile.h"
#include "Character/EveCharacterBase.h"


void UEveProjectileSpawn::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UEveProjectileSpawn::SpawnProjectile(const FVector& ProjectileTargetLocation, bool bOverridePitch, float PitchOverride)
{
	// todo: Socket을 무기, 왼손, 오른손 등에 따라서 다르게 가져오기
	AEveCharacterBase* OwnerCharacter = Cast<AEveCharacterBase>(GetAvatarActorFromActorInfo());
	const FVector SocketLocation = OwnerCharacter->GetMesh()->GetSocketLocation(FName("RightHandSocket"));
	
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
		
	AEveProjectile* Projectile = GetWorld()->SpawnActorDeferred<AEveProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	// todo: damage 로직 수정
	UAbilitySystemComponent* OwnerASC = OwnerCharacter->GetAbilitySystemComponent();
	Projectile->DamageSpecHandle = OwnerASC->MakeOutgoingSpec(DamageEffectClass, 1, OwnerASC->MakeEffectContext());
		
	Projectile->FinishSpawning(SpawnTransform);
}
