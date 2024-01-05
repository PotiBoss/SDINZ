// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SDINZ : ModuleRules
{
	public SDINZ(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "ProceduralMeshComponent" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "GameplayTasks", "SlateCore" });
    }
}
