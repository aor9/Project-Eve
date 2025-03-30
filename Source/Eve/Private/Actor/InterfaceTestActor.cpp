// Copyright aor9


#include "Actor/InterfaceTestActor.h"

#include "EveDebugHelper.h"


AInterfaceTestActor::AInterfaceTestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	SetRootComponent(Mesh);
}

void AInterfaceTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInterfaceTestActor::Interact()
{
	
}

void AInterfaceTestActor::BeginFocus()
{
	Debug::Print(TEXT("범위 내에 Interaction 가능한 Actor가 들어옴."));
}

void AInterfaceTestActor::EndFocus()
{
	Debug::Print(TEXT("Interaction 가능한 Actor가 범위 밖으로 나감."));
}

void AInterfaceTestActor::BeginInteract()
{
	Debug::Print(TEXT("Begin Interact"));
}

void AInterfaceTestActor::EndInteract()
{
	Debug::Print(TEXT("End Interact"));
}
