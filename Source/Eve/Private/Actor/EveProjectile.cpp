// Copyright aor9


#include "Actor/EveProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Eve.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/EveAbilitySystemLibrary.h"
#include "AbilitySystem/EveAttributeSet.h"
#include "Character/EveCharacterBase.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


class UEveAttributeSet;

AEveProjectile::AEveProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AEveProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);
	SetReplicateMovement(true);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEveProjectile::OnSphereOverlap);
	Sphere->OnComponentHit.AddDynamic(this, &AEveProjectile::OnSphereHit);


	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}

void AEveProjectile::OnHit()
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	if (LoopingSoundComponent)
	{
		LoopingSoundComponent->Stop();
		LoopingSoundComponent->DestroyComponent();
	}
	bHit = true;
}

void AEveProjectile::Destroyed()
{
	if (LoopingSoundComponent)
	{
		LoopingSoundComponent->Stop();
		LoopingSoundComponent->DestroyComponent();
	}
	if (!bHit) OnHit();
	
	Super::Destroyed();
}

void AEveProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValidOverlap(OtherActor)) return;
	if (!bHit) OnHit();

	AEveCharacterBase* CharacterBase = Cast<AEveCharacterBase>(OtherActor);

	// todo: damage 처리
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		TargetASC->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());
		if (UEveAttributeSet* TargetAttributes = Cast<UEveAttributeSet>(CharacterBase->GetAttributeSet()))
		{
			float CurrentHealth = TargetAttributes->GetHealth();
			if (CurrentHealth <= 0.f)
			{
				CharacterBase->Die();
			}
		}
	}
	
	Destroy();
}

void AEveProjectile::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!bHit)
	{
		OnHit(); // 시각/사운드 이펙트 실행
	}

	Destroy();
}

bool AEveProjectile::IsValidOverlap(AActor* OtherActor)
{
	// if (DamageEffectParams.SourceAbilitySystemComponent == nullptr) return false;
	// if (SourceAvatarActor == OtherActor) return false;
	// if (!UEveAbilitySystemLibrary::IsNotFriend(SourceAvatarActor, OtherActor)) return false;
	
	return true;
}

