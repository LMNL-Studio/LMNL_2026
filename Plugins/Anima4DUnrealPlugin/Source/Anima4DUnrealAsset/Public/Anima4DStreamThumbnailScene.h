#pragma once

#include "CoreMinimal.h"
#include "PreviewScene.h"
#include "ThumbnailHelpers.h"

class ANIMA4DUNREALASSET_API FAnima4DStreamThumbnailScene : public FThumbnailPreviewScene
{
public:
	/** Constructor */
	FAnima4DStreamThumbnailScene();

	/** Sets the static mesh to use in the next GetView() */
	//void SetStaticMesh(class UStaticMesh* StaticMesh);
	void SetAnima4DStream(class UAnima4DStreamInfo* Anima4DStream);

	/** Sets override materials for the static mesh  */
	void SetOverrideMaterials(const TArray<class UMaterialInterface*>& OverrideMaterials);

protected:
	// FThumbnailPreviewScene implementation
	virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;

private:
	/** The static mesh actor used to display all static mesh thumbnails */
	class AAnima4DActor* PreviewActor;
};


