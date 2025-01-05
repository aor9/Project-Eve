// Copyright aor9


#include "Animation/EveAnimInstance.h"

#include "Character/EveCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


UEveAnimInstance::UEveAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UEveAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EveCharacter = Cast<AEveCharacter>(TryGetPawnOwner());
}

void UEveAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if(EveCharacter == nullptr)
	{
		EveCharacter = Cast<AEveCharacter>(TryGetPawnOwner());
	}
	if(EveCharacter == nullptr)	return;

	Velocity = EveCharacter->GetVelocity();
	Velocity.Z = 0.f;

	// 캐릭터의 이동방향, 바라보는 방향의 내적 값 구하기
	FVector2D Velocity2D = FVector2D(Velocity.X, Velocity.Y);
	MoveDirVector2D = Velocity2D.GetSafeNormal();
	
	ForwardVector = EveCharacter->GetActorForwardVector();
	ForwardVector2D = FVector2D(ForwardVector.X, ForwardVector.Y).GetSafeNormal();
	ForwardDot = FVector2D::DotProduct(MoveDirVector2D, ForwardVector2D);
	
	RightVector = EveCharacter->GetActorRightVector();
	RightVector2D = FVector2D(RightVector.X, RightVector.Y).GetSafeNormal();
	RightDot = FVector2D::DotProduct(MoveDirVector2D, RightVector2D);
	
	GroundSpeed = Velocity.Size();
	bShouldMove = EveCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

}
