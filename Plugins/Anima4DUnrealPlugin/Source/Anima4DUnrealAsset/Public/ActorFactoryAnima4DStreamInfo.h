#pragma once

#if WITH_EDITOR

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ActorFactories/ActorFactory.h"
#include "UEVersionCompare.h"
#include "ActorFactoryAnima4DStreamInfo.generated.h"


class AActor;
struct FAssetData;

UCLASS(MinimalAPI, config=Editor)
class UActorFactoryAnima4DStreamInfo: public UActorFactory
{
	GENERATED_UCLASS_BODY()

	//~ Begin UActorFactory Interface
	virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;
	virtual void PostSpawnActor( UObject* Asset, AActor* NewActor) override;
#if ENGINE_VERSION_AT_MOST(5,3)
	virtual void PostCreateBlueprint(UObject* Asset, AActor* CDO) override;
#endif
	virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;
	virtual FQuat AlignObjectToSurfaceNormal(const FVector& InSurfaceNormal, const FQuat& ActorRotation) const override;
	//~ End UActorFactory Interface
};

#endif
