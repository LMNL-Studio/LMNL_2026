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

#include "AxyzGPUImage.h"
#include "RHI.h"
#include "UEVersionCompare.h"

class AnimaUnrealGPUImage : public AxyzGPUImage {
private:

#if ENGINE_VERSION_AT_LEAST(5,3)
	FTextureRHIRef unrealTexture;
#else
	FTexture2DRHIRef unrealTexture;
#endif
	AxyzGPUImage *renderImage;
public:
#if ENGINE_VERSION_AT_LEAST(5,3)
	AnimaUnrealGPUImage(int GPUIndex, AxyzImage::Format format, uint32_t width, uint32_t height, FTextureRHIRef unrealTexture);
	FTextureRHIRef getTexture() const;
#else
	AnimaUnrealGPUImage(int GPUIndex, AxyzImage::Format format, uint32_t width, uint32_t height, FTexture2DRHIRef unrealTexture);
	FTexture2DRHIRef getTexture() const;
#endif
	virtual ~AnimaUnrealGPUImage();
	virtual void *getMappedArray() const;
	virtual bool isEmpty() const;
};