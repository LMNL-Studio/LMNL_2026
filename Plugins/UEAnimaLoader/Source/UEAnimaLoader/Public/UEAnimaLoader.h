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

#define WIN32_LEAN_AND_MEAN
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;
class FExtender;

class FUEAnimaLoaderModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void AddToolbarExtension(FToolBarBuilder& Builder);
	static void AddMenuExtensionButtons(FMenuBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);
	void ActionGalleryClicked(int param);

	TSharedPtr<class FUICommandList> PluginCommands;
};