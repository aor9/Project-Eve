// Copyright aor9


#include "EveGameplayTags.h"


namespace EveGameplayTags
{
	// ** Inputs
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Move, "Input.Action.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Roll, "Input.Action.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Input_LMB, "Input.LMB");
	UE_DEFINE_GAMEPLAY_TAG(Input_RMB, "Input.RMB");
	UE_DEFINE_GAMEPLAY_TAG(Input_Q, "Input.Q");
	UE_DEFINE_GAMEPLAY_TAG(Input_E, "Input.E");
	
	// ** Player
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Sword, "Player.Ability.Attack.Light.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Sword, "Player.Ability.Attack.Heavy.Sword");

	// ** Player State
	UE_DEFINE_GAMEPLAY_TAG(Player_State_NoMove, "Player.State.NoMove");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Rolling, "Player.State.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Stunned, "Player.State.Stunned");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Bleeding, "Player.State.Bleeding");
	
	// ** Player Weapons
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Shield, "Player.Weapon.Shield");

	// ** Enemy
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");
}