// Copyright aor9


#include "Animation/EvePlayerAnimInstance.h"

#include "Character/EveCharacter.h"
#include "Character/EveCharacterBase.h"


void UEvePlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(OwningCharacter)
	{
		OwningPlayerCharacter = Cast<AEveCharacter>(OwningCharacter);
	}
}

void UEvePlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if(bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
	
	if(!OwningPlayerCharacter || !OwningMovementComponent)
	{
		return;
	}
	
	FVector Velocity = OwningCharacter->GetVelocity();
	FVector2D Velocity2D = FVector2D(Velocity.X, Velocity.Y);
	MoveDirVector2D = (Velocity2D.SquaredLength() > KINDA_SMALL_NUMBER) ? Velocity2D.GetSafeNormal() : FVector2D::ZeroVector;
	
	ForwardVector = OwningCharacter->GetActorForwardVector();
	ForwardVector2D = FVector2D(ForwardVector.X, ForwardVector.Y);
	ForwardVector2D = (ForwardVector2D.SquaredLength() > KINDA_SMALL_NUMBER) ? ForwardVector2D.GetSafeNormal() : FVector2D::ZeroVector;
	ForwardDot = FVector2D::DotProduct(MoveDirVector2D, ForwardVector2D);
	
	RightVector = OwningCharacter->GetActorRightVector();
	RightVector2D = FVector2D(RightVector.X, RightVector.Y);
	RightVector2D = (RightVector2D.SquaredLength() > KINDA_SMALL_NUMBER) ? RightVector2D.GetSafeNormal() : FVector2D::ZeroVector;
	RightDot = FVector2D::DotProduct(MoveDirVector2D, RightVector2D);
}
