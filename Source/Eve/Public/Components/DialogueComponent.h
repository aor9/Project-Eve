// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/DialogueStruct.h"
#include "DialogueComponent.generated.h"

class UWidgetComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVE_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDialogueComponent();
	void StartDialogue();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category= "Dialogue")
	TObjectPtr<UDataTable> DialogueDataTable;

	UPROPERTY(EditAnywhere, Category= "Dialogue")
	FName StartRowName;

	UPROPERTY(VisibleInstanceOnly, Category= "Dialogue")
	FDialogueData InstanceDialogueData;
};
