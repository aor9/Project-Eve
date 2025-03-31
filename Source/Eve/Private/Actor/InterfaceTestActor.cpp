// Copyright aor9


#include "Actor/InterfaceTestActor.h"

#include "EveDebugHelper.h"
#include "Character/EveCharacter.h"
#include "Components/WidgetComponent.h"
#include "UI/Widgets/InteractionWidget.h"


AInterfaceTestActor::AInterfaceTestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidgetComponent->SetupAttachment(RootComponent);
	InteractionWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidgetComponent->SetVisibility(false);
}

void AInterfaceTestActor::BeginPlay()
{
	Super::BeginPlay();

	InteractableData = InstanceInteractableData;
}

void AInterfaceTestActor::Interact(AEveCharacter* Character)
{
	Debug::Print(TEXT("Interact"));
}

void AInterfaceTestActor::BeginFocus()
{
	Debug::Print(TEXT("범위 내에 Interaction 가능한 Actor가 들어옴."));
	InteractionWidgetComponent->SetVisibility(true);

	UInteractionWidget* Widget = Cast<UInteractionWidget>(InteractionWidgetComponent->GetUserWidgetObject());
	if(Widget)
	{
		Widget->UpdateWidget(&InteractableData);
	}
}

void AInterfaceTestActor::EndFocus()
{
	Debug::Print(TEXT("Interaction 가능한 Actor가 범위 밖으로 나감."));
	InteractionWidgetComponent->SetVisibility(false);
}

void AInterfaceTestActor::BeginInteract()
{
	Debug::Print(TEXT("Begin Interact"));
}

void AInterfaceTestActor::EndInteract()
{
	Debug::Print(TEXT("End Interact"));
}
