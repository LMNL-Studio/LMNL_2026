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

#pragma once

#include "Modules/ModuleManager.h"

class FAnima4DUnrealPluginModule : public IModuleInterface
{
public:

    FAnima4DUnrealPluginModule();
    
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

    static inline FAnima4DUnrealPluginModule& Get()
    {
        return FModuleManager::LoadModuleChecked< FAnima4DUnrealPluginModule >("Anima4DUnrealPlugin");
    }
    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("Anima4DUnrealPlugin");
    }
	
	bool HandleSettingsSaved();
	void RegisterSettings();
	void UnregisterSettings() ;

};
