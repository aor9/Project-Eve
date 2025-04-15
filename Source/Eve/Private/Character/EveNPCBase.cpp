// Copyright aor9


#include "Character/EveNPCBase.h"

#include "EveDebugHelper.h"
#include "Components/DialogueComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Widgets/InteractionWidget.h"


class UInteractionWidget;

AEveNPCBase::AEveNPCBase()
{	
	PrimaryActorTick.bCanEverTick = true;

	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidgetComponent->SetupAttachment(RootComponent);
	InteractionWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidgetComponent->SetVisibility(false);
	InteractionWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	NPCDialogue = CreateDefaultSubobject<UDialogueComponent>(TEXT("NPC Dialogue Component"));
}

void AEveNPCBase::BeginPlay()
{
	Super::BeginPlay();

	InstanceInteractableData.InteractableType = EInteractableType::Toggle;
	InstanceInteractableData.Name = FText::FromName(NPCName);
	InteractableData = InstanceInteractableData;

	if(UInteractionWidget* Widget = Cast<UInteractionWidget>(InteractionWidgetComponent->GetUserWidgetObject()))
	{
		Widget->UpdateWidget(&InteractableData);
	}
}

void AEveNPCBase::BeginFocus()
{
	InteractionWidgetComponent->SetVisibility(true);

	if(UInteractionWidget* Widget = Cast<UInteractionWidget>(InteractionWidgetComponent->GetUserWidgetObject()))
	{
		Widget->UpdateWidget(&InteractableData);
	}
}

void AEveNPCBase::EndFocus()
{
	InteractionWidgetComponent->SetVisibility(false);
}

void AEveNPCBase::Interact(AEveCharacter* EveCharacter)
{
	NPCDialogue->StartDialogue();
}
