// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "EveAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class EVE_API UEveAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UEveAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// Vital Attributes
	// Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Health", Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_MaxHealth", Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	// Body Temperature
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_BodyTemperature", Category = "Vital Attributes")
	FGameplayAttributeData BodyTemperature;
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, BodyTemperature);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_MaxBodyTemperature", Category = "Vital Attributes")
	FGameplayAttributeData MaxBodyTemperature;
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, MaxBodyTemperature);

	UFUNCTION()
	void OnRep_BodyTemperature(const FGameplayAttributeData& OldBodyTemperature) const;
	
	UFUNCTION()
	void OnRep_MaxBodyTemperature(const FGameplayAttributeData& OldMaxBodyTemperature) const;

	// Hunger
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Hunger", Category = "Vital Attributes")
	FGameplayAttributeData Hunger;
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, Hunger);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_MaxHunger", Category = "Vital Attributes")
	FGameplayAttributeData MaxHunger;
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, MaxHunger);

	UFUNCTION()
	void OnRep_Hunger(const FGameplayAttributeData& OldHunger) const;
	
	UFUNCTION()
	void OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger) const;


	// Combat Attributes
	// Stamina
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Stamina", Category = "Combat Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_MaxStamina", Category = "Combat Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, MaxStamina);

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;
	
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;

protected:
	
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	
};
