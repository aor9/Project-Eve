// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractionInterface.h"
#include "EveNPCBase.generated.h"

class UDialogueComponent;
class UWidgetComponent;

UCLASS()
class EVE_API AEveNPCBase : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:
	AEveNPCBase();
	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void Interact(AEveCharacter* EveCharacter) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "NPC")
	TObjectPtr<UWidgetComponent> InteractionWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category= "NPC")
	TObjectPtr<UDialogueComponent> DialogueComponent;

	UPROPERTY(EditAnywhere, Category= "NPC")
	FName NPCName;

	UPROPERTY(VisibleInstanceOnly, Category= "NPC")
	FInteractableData InstanceInteractableData;
};
