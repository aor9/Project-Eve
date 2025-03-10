// Copyright aor9

#pragma once

#include "NativeGameplayTags.h"

/**
 * 
 */
namespace EveGameplayTags
{
	// ** Inputs
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Roll);
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_LMB);
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_RMB);
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Q);
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_E);

	// ** Player
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Sword);
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Sword);

	// ** Player State
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_NoMove);
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Rolling);
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Stunned);
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Bleeding);

	// ** Player Weapon
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Shield);

	// ** Enemy
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	// ** Abilities
	EVE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Attack);
};
