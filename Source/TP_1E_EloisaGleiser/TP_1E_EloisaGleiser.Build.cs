// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TP_1E_EloisaGleiser : ModuleRules
{
	public TP_1E_EloisaGleiser(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TP_1E_EloisaGleiser",
			"TP_1E_EloisaGleiser/Variant_Platforming",
			"TP_1E_EloisaGleiser/Variant_Platforming/Animation",
			"TP_1E_EloisaGleiser/Variant_Combat",
			"TP_1E_EloisaGleiser/Variant_Combat/AI",
			"TP_1E_EloisaGleiser/Variant_Combat/Animation",
			"TP_1E_EloisaGleiser/Variant_Combat/Gameplay",
			"TP_1E_EloisaGleiser/Variant_Combat/Interfaces",
			"TP_1E_EloisaGleiser/Variant_Combat/UI",
			"TP_1E_EloisaGleiser/Variant_SideScrolling",
			"TP_1E_EloisaGleiser/Variant_SideScrolling/AI",
			"TP_1E_EloisaGleiser/Variant_SideScrolling/Gameplay",
			"TP_1E_EloisaGleiser/Variant_SideScrolling/Interfaces",
			"TP_1E_EloisaGleiser/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
