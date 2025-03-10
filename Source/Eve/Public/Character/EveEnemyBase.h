// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Character/EveCharacterBase.h"
#include "DataAssets/CharacterClassInfo.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EveEnemyBase.generated.h"

class UWidgetComponent;
class UEnemyCombatComponent;
class UBehaviorTree;
class AEveAIController;
/**
 * 
 */
UCLASS()
class EVE_API AEveEnemyBase : public AEveCharacterBase
{
	GENERATED_BODY()
	
	
public:
	AEveEnemyBase();
	
	virtual void PossessedBy(AController* NewController) override;

	void SetHitReacting(bool bReacting);

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxHealthChanged;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AEveAIController> EveAIController;

private:
	float MaxWalkSpeed = 150.f;

	void GiveStartupAbilities() const;

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const {return EnemyCombatComponent;}
	
};
