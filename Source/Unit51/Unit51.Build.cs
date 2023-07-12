// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Unit51 : ModuleRules
{
	public Unit51(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayTasks" });
	}
}
