// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Eve : ModuleRules
{
	public Eve(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[]
		{
			"Eve",
		});
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", 
			"GameplayAbilities", "GameplayTags", "GameplayTasks", "Niagara", "AIModule", "SlateCore", "Slate", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "MotionWarping" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
