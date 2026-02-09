/**
*	ANIMA(c) COPYRIGHT (c) 2025 CHAOS. ALL RIGHTS RESERVED.
*
*	CONFIDENTIAL INFORMATION OF CHAOS. NOT FOR DISCLOSURE OR DISTRIBUTION
*	WITHOUT CHAOS' PRIOR WRITTEN CONSENT. THIS SOFTWARE CONTAINS CODE, TECHNIQUES AND KNOW-HOW
*	WHICH IS CONFIDENTIAL AND PROPRIETARY TO CHAOS. 
*
*	ANIMA(c) IS A REGISTERED TRADEMARKS OF CHAOS IN THE USA, EU AND/OR OTHER COUNTRIES.
*	ALL OTHER BRAND NAMES, PRODUCT NAMES OR TRADEMARKS BELONG TO THEIR RESPECTIVE HOLDERS.
*/

using System.IO;
using UnrealBuildTool;
using System;

public class UEAnimaAssets : ModuleRules
{
    public UEAnimaAssets(ReadOnlyTargetRules Target) : base(Target)
    {
        bPrecompile = false;
        bUsePrecompiled = !bPrecompile;
        if (bPrecompile) {
           PrecompileForTargets = PrecompileTargetsType.Any;
        }

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnableExceptions = true;

        string PublicDir = Path.Combine(ModuleDirectory, "Public");
        if (Directory.Exists(PublicDir))
        {
            PublicIncludePaths.AddRange(
                new string[] {
            PublicDir
                }
            );
        }

        PrivateIncludePaths.AddRange(new string[] {
            Path.Combine(ModuleDirectory, "Private"),
        });
        Console.Out.WriteLine("Anima Asset Plugin ModuleDirectory: " + ModuleDirectory);

        PublicDependencyModuleNames.AddRange(new string[] {
                "Core",
                "CoreUObject",
                "AssetRegistry",
                "Engine"
            }
        );
    }	
}
