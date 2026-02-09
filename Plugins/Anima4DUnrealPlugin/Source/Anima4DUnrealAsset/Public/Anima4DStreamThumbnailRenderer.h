#pragma once

/**
 *
 * This thumbnail renderer displays a given static mesh
 */

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ThumbnailRendering/DefaultSizedThumbnailRenderer.h"
#include "Anima4DStreamThumbnailRenderer.generated.h"

class FCanvas;
class FRenderTarget;

UCLASS(config=Editor)
class  UAnima4DStreamThumbnailRenderer : public UDefaultSizedThumbnailRenderer
{
	GENERATED_UCLASS_BODY()

	// Begin UThumbnailRenderer Object
	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily) override;
	// End UThumbnailRenderer Object


	// UObject implementation
	virtual void BeginDestroy() override;
	virtual bool AllowsRealtimeThumbnails(UObject* Object) const override { return false; }

private:
	class FAnima4DStreamThumbnailScene* ThumbnailScene;
};


