using System.IO;
using UnrealBuildTool;
using System;

public class UEAnimaLoader : ModuleRules
{
    public UEAnimaLoader(ReadOnlyTargetRules Target) : base(Target)
    {
        bPrecompile = false;
        bUsePrecompiled = !bPrecompile;
        if (bPrecompile) {
           PrecompileForTargets = PrecompileTargetsType.Any;
        }

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

       // ------------------------------------------------------------
        // Includes (avoid warnings if folders don't exist)
        // ------------------------------------------------------------
        string PublicDir = Path.Combine(ModuleDirectory, "Public");
        if (Directory.Exists(PublicDir))
        {
            PublicIncludePaths.Add(PublicDir);
        }

        string PrivateDir = Path.Combine(ModuleDirectory, "Private");
        if (Directory.Exists(PrivateDir))
        {
            PrivateIncludePaths.Add(PrivateDir);
        }

        Console.Out.WriteLine("Plugin ModuleDirectory: " + ModuleDirectory);

        PublicDependencyModuleNames.AddRange(new string[] {
               "Core",
                "RHI",
                "CoreUObject",
                "AssetRegistry",
                "Engine",
                "RenderCore",
                "Slate",
                "SlateCore",
                "EditorStyle",
                "InputCore",
                "UnrealEd",
                "AssetTools",
                "MeshBuilder",
                "Projects",
                "RawMesh",
                "MainFrame",
                "LevelSequence",
                "MovieScene",
            }
        );

        PrivateDependencyModuleNames.AddRange(new string[] {
                "SourceControl",
                "Anima4DUnrealPlugin",
                "Anima4DUnrealAsset",
                "UEAnimaAssets",
                "EngineSettings"
            }
        );

        if ((Target.Version.MajorVersion > 5) ||
            (Target.Version.MajorVersion == 5 && Target.Version.MinorVersion >= 7))
        {
            PrivateDependencyModuleNames.Add("StaticMeshEditor");
        }

        Console.Out.WriteLine("Anima Plugin using: " + Target.BuildVersion);

        if (Target.Type == TargetRules.TargetType.Editor)
        {
            if (Target.BuildVersion.Contains("5.") == true || Target.BuildVersion.Contains("UE5") == true)
            {
                PrivateDependencyModuleNames.Add("DeveloperToolSettings");
                PrivateDependencyModuleNames.Add("PhysicsUtilities");
                PrivateDependencyModuleNames.Add("UnrealEd");
            }
        }

        if (Target.BuildVersion.Contains("4.21") == false && Target.BuildVersion.Contains("4.23") == false)
        {
            PrivateDependencyModuleNames.AddRange(new string[] {
               "SkeletalMeshUtilitiesCommon",
            });
        }
        else
        {
            Console.Out.WriteLine("Without SkeletalMeshUtilitiesCommon");
        }

        PublicDelayLoadDLLs.Add("Anima2.PluginAPI.dll");
    }
}