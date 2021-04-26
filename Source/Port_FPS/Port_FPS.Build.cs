// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Port_FPS : ModuleRules
{
	public Port_FPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "OnlineSubsystem", "OnlineSubsystemSteam", "UMG" });
	}
}
