// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Arena : ModuleRules
{
	public Arena(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "OnlineSubsystem" , "OnlineSubsystemUtils" , "SlateCore" });
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
    }
}
