// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EveAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class EVE_API AEveAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEveAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

private:
	
};
