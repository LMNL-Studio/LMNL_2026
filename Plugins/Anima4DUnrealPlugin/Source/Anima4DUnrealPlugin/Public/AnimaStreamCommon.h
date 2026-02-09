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

#include <vector>
#include <assert.h>
#include <array>
#include "Engine/World.h"

class UWorld;

namespace Anima {
	enum StreamQuality : int {
		Quality_Level_0 = 0,	// High
		Quality_Level_1,		// Medium
		Quality_Level_2,		// Low 
		Quality_Level_3,		// Lowest
		Quality_Level_Count
	};
	enum EScalability { LowScalabilitySetting = 0, MediumScalabilitySetting, HighScalabilitySetting, EpicScalabilitySetting, CinematicScalabilitySetting };

	// Warning: call this only from Game thread
	bool IsCinematic_GameThread();
	// Warning: call this only from Game thread
	bool IsEditorViewport(UWorld* World);

	Anima::StreamQuality GetViewportMaxStreamQuality_GameThread();

	// Screen size threshold for quality levels.
	const std::array<float, StreamQuality::Quality_Level_Count> Anima4DViewportScreenSizePerQuality = { 
		1.00f, 
		0.40f, 
		0.20f,
		0.1f
	};

}
