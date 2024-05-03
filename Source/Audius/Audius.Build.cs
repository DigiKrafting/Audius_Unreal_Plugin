/*

Copyright 2024 Audius

License: https://www.unrealengine.com/en-US/eula/content

*/

using UnrealBuildTool;

public class Audius : ModuleRules
{
	public Audius(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);

        PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Media",
                "MediaAssets",
                "MediaUtils",
				"UMG"
				// ... add other public dependencies that you statically link with here ...
			}
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "HTTP",
                "Json",
                "JsonUtilities",
				"AudioMixer"
            }
            );
        // "MediaAssets",
        DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{

				// ... add any modules that your module loads dynamically here ...
			}
            );

	}

}
