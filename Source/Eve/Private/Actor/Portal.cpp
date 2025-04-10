// Copyright aor9


#include "Actor/Portal.h"

#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/InteractionWidget.h"


APortal::APortal()
{
	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>("Portal Mesh");
	SetRootComponent(PortalMesh);

	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidgetComponent->SetupAttachment(RootComponent);
	InteractionWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidgetComponent->SetVisibility(false);
	InteractionWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
}

void APortal::BeginPlay()
{
	Super::BeginPlay();

	InstanceInteractableData.InteractableType = EInteractableType::Toggle;
	InstanceInteractableData.Name = FText::FromName(TargetLevelName);
	InstanceInteractableData.Action = FText::FromString("Enter");
	InteractableData = InstanceInteractableData;

	if(UInteractionWidget* Widget = Cast<UInteractionWidget>(InteractionWidgetComponent->GetUserWidgetObject()))
	{
		Widget->UpdateWidget(&InteractableData);
	}
}

void APortal::BeginFocus()
{
	InteractionWidgetComponent->SetVisibility(true);

	if(UInteractionWidget* Widget = Cast<UInteractionWidget>(InteractionWidgetComponent->GetUserWidgetObject()))
	{
		Widget->UpdateWidget(&InteractableData);
	}
}

void APortal::EndFocus()
{
	InteractionWidgetComponent->SetVisibility(false);
}

void APortal::Interact(AEveCharacter* EveCharacter)
{
	if(EveCharacter)
	{
		// todo: 레벨 이동할 때 플레이어의 데이터들이 모두 저장되어 있어야함.
		TravelToLevel();
	}
}

void APortal::TravelToLevel() const
{
	if(!TargetLevelName.IsNone())
	{
		UGameplayStatics::OpenLevel(this, TargetLevelName);
	}
}
