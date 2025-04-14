// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVE_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDialogueComponent();

protected:
	UPROPERTY(EditAnywhere, Category= "Dialogue")
	TObjectPtr<UDataTable> DialogueDataTable;

	UPROPERTY(EditAnywhere, Category= "Dialogue")
	FName StartRowName;

	UPROPERTY(EditAnywhere, Category= "Dialogue")
	FText NPCName;
};
