#pragma once

#include "Materials/MaterialExpression.h"
#include "Anima4DVertexVelocityWS.generated.h"

UCLASS(HideCategories = Object)
class ANIMA4DUNREALASSET_API UAnima4DVertexVelocityWS : public UMaterialExpression
{
	GENERATED_UCLASS_BODY()
		
	UPROPERTY()
	FExpressionInput Texture;

	UPROPERTY()
	FExpressionInput Coordinates;

#if WITH_EDITOR
	virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;
	virtual void GetCaption(TArray<FString>& OutCaptions) const override;

	virtual uint32 GetInputType(int32 InputIndex) override;
#endif // WITH_EDITOR
};
