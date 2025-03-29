// Copyright aor9


#include "Actor/InterfaceTestActor.h"

#include "EveDebugHelper.h"


AInterfaceTestActor::AInterfaceTestActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AInterfaceTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInterfaceTestActor::OnClick()
{
	
}

void AInterfaceTestActor::SetClickable(bool bClickable)
{
	if(bClickable)
	{
		Debug::Print(TEXT("범위 내에 Interaction 가능한 Actor가 들어옴."));
	}
	else
	{
		Debug::Print(TEXT("Interaction 가능한 Actor가 범위 밖으로 나감."));
	}
	
	bIsClickable = bClickable;
}