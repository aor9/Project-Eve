// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataAssets/CharacterClassInfo.h"
#include "EveAbilitySystemLibrary.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class EVE_API UEveAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintCallable, Category = "EveAbilitySystemLibrary")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);
	
};
