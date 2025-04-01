// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "InteractionInterface.generated.h"

class AEveCharacter;

UENUM()
enum EInteractableType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"),
	NonPlayerCharacter UMETA(DisplayName = "NonPlayerCharacter"),
	Device UMETA(DisplayName = "Device"),
	Toggle UMETA(DisplayName = "Toggle"),
	Container UMETA(DisplayName = "Container")
};

USTRUCT()
struct FInteractableData
{
	GENERATED_BODY()

	FInteractableData() :
	InteractableType(EInteractableType::Pickup), Name(FText::GetEmpty()),
	Action(FText::GetEmpty()), Quantity(0), InteractionDuration(0.f)
	{
		
	};

	UPROPERTY(EditInstanceOnly)
	TEnumAsByte<EInteractableType> InteractableType;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	FText Action;

	// used only for pickups
	UPROPERTY(EditInstanceOnly)
	int8 Quantity;

	// used for things like doors, that requires an interaction timer
	UPROPERTY(EditInstanceOnly)
	float InteractionDuration;
};

UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class EVE_API IInteractionInterface
{
	GENERATED_BODY()

public:
	virtual void BeginFocus() = 0;
	virtual void EndFocus() = 0;
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual void Interact(AEveCharacter* EveCharacter) = 0;

	FInteractableData InteractableData;
};
