// Copyright aor9

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EveGameplayTags.h"
#include "DataAssets/Input/EveInputData.h"
#include "EveInputComponent.generated.h"
/**
 * 
 */
UCLASS()
class EVE_API UEveInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UEveInputData* InputData, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UEveInputComponent::BindAbilityActions(const UEveInputData* InputData, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputData);

	for (const FEveInputAction& Action : InputData->InputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if(Action.InputTag != EveGameplayTags::Input_LMB)
			{
				if (ReleasedFunc)
				{
					BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
				}
			
				if (HeldFunc)
				{
					BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
				}
			}
		}
	}
}
