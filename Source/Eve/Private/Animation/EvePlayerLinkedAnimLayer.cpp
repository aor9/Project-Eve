// Copyright aor9


#include "Animation/EvePlayerLinkedAnimLayer.h"

#include "Animation/EvePlayerAnimInstance.h"


UEvePlayerAnimInstance* UEvePlayerLinkedAnimLayer::GetPlayerAnimInstance() const
{
	return Cast<UEvePlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
