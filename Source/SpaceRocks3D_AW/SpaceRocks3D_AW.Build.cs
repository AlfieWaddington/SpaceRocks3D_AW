// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SpaceRocks3D_AW : ModuleRules
{
	public SpaceRocks3D_AW(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // This line tells the compiler to treat the root of this module as a valid include path.
        // It allows #include "Projectiles/Projectile.h" to work correctly.
        PublicIncludePaths.AddRange(new string[] { ModuleDirectory });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
