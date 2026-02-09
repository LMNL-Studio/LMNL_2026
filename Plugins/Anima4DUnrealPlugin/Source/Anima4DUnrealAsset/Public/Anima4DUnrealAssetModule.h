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

class FAnima4DUnrealAssetModule : public IModuleInterface
{
public:

	FAnima4DUnrealAssetModule();

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static inline FAnima4DUnrealAssetModule & Get()
	{
		return FModuleManager::LoadModuleChecked< FAnima4DUnrealAssetModule  >("Anima4DUnrealAsset");
	}
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Anima4DUnrealAsset ");
	}

	void RegisterThumbnailRenderers();
	
	void UnregisterThumbnailRenderers();

private:

	// Callback for when the settings were saved.
	bool HandleSettingsSaved();
	void RegisterSettings();
	void UnregisterSettings();
};
