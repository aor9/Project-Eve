// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Character/EveCharacterBase.h"
#include "EveEnemyBase.generated.h"

class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class EVE_API AEveEnemyBase : public AEveCharacterBase
{
	GENERATED_BODY()
	
	
public:
	AEveEnemyBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const {return EnemyCombatComponent;}
	
};
