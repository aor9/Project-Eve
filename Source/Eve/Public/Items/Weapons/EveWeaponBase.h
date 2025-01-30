// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EveWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class EVE_API AEveWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEveWeaponBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* WeaponCollisionBox;

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
	
};
