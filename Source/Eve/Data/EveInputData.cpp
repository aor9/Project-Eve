// Copyright aor9


#include "Data/EveInputData.h"


const UInputAction* UEveInputData::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FEveInputAction& Action : InputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Can't find InputAction for InputTag [%s]"), *InputTag.ToString());

	return nullptr;
}
