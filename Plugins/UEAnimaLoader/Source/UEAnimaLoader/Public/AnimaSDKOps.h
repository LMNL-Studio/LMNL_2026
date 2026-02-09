#pragma once

#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "PackageTools.h"
#include "HelperFunctions.h"
#include "RawMesh.h"
#include "Engine/SkeletalMesh.h"
#include "Internationalization/Internationalization.h"
#include "Runtime/Launch/Resources/version.h"
#include "Layers/LayersSubsystem.h"
#include "IAssetTools.h"
#include "PackageTools.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "MeshUtilities.h"
#include "SkeletalMeshTypes.h"
#include "Rendering/SkeletalMeshLODModel.h"
#include "Rendering/SkeletalMeshModel.h"
#include "Rendering/MultiSizeIndexContainer.h"
#include "Misc/ScopedSlowTask.h"
#if ENGINE_MAJOR_VERSION >= 5
	#include "Engine/SkinnedAssetCommon.h"
#endif

//#include "AnimaImporterPrivatePCH.h"
#include "UnrealEd.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"		// For inline LoadModuleChecked()

#include <sstream>
#include "ObjectTools.h"
#include "AssetRegistryModuleWrapper.h"

#include "../Public/AnimaAutogenIncludeAPI.h"
#include "UEVersionCompare.h"

#include "Animation/AnimSequence.h"

#include "UEAnimaInterface.h"

#include "AnimaCommon.h"



class ActorAnimation
{
public:
	ActorAnimation(const int nBones = 0);
	void AddDefaulted(const int nBones);
	void Empty();
	void Shrink();

#if ENGINE_VERSION_AT_LEAST(5,0)
	TArray<TArray<FVector3f>> ActorAnimationPositions;
	TArray<TArray<FQuat4f>> ActorAnimationRotations;
#else
	TArray<TArray<FVector>> ActorAnimationPositions;
	TArray<TArray<FQuat>> ActorAnimationRotations;
#endif
	TArray<float> ActorAnimationScale; // needed for root bone visibility
	FBox BoundingBox;
};


class AnimaListener : public Anima::PluginListener
{
public:
	AnimaListener();
	// Progress comming from Anima Api
	virtual void progressEvent(Anima::PluginProgress progress);
	static FScopedSlowTask* ProgressTask;

	void afterIpcActionEvent(Anima::PluginIpcAction message) {};
	void beforeIpcActionEvent(Anima::PluginIpcAction message) {};
};

class AnimaSceneImporter
{
public:
	AnimaSceneImporter(FScopedSlowTask *Progress);
	bool ImportScene(UWorld* World, UPackage* Package, const FString actualFilePath);
	bool OpenGallery(UWorld* World, UPackage* Package);
	bool OpenDropGallery(UWorld* World, UPackage* Package);
	bool ForceImportYAsset(UWorld* World, UPackage* Package, TArray<FString> paths, TArray<FString> names, const bool ignoreRiggedAnd4D);
	static void DeleteAPI();
	static Anima::PluginAPI* getAPI();

private:
	//plugin API is initialized only once
	static Anima::PluginAPI *anima_plugin_api;
	FScopedSlowTask *ProgressTask;
	AnimaListener Listener;
	bool ParseScene(UWorld* World, UPackage* Package);
	bool ImportYFile(const FString inputPath, const FString baseName, UWorld* World, UPackage* Package, FScopedSlowTask* Progress, const float progressAdvance, bool forceSaving, const bool ignoreRiggedAnd4D, bool CreateBaseNamePackage = false);

	UStaticMesh* CreateAnimaStaticMesh(UWorld* World, const Anima::PluginMesh *animaMesh, const bool computeLODs, 
									   FString baseName, Anima::PluginMaterial* Materials, UPackage* MeshesPackage, 
									   UPackage* MaterialsPackage, UPackage** ThisMeshPackage = nullptr);
	bool CreateAnimaMaterials(UWorld* World, UPackage* Package, UPackage* TexturesPackage);
	bool CreateAnimaStaticMeshes(UWorld* World, UPackage* MeshesPackage, UPackage* MaterialsPackage, const bool createRBLods);
	bool CreateAnimaSkeletalMeshes(UWorld* World, UPackage* MeshesPackage, UPackage* MaterialsPackage, UPackage* AnimPackage);
	bool CreateAnimaSkeletalEscalators(UWorld* World, UPackage* MeshesPackage, UPackage* MaterialsPackage, UPackage* AnimPackage);
	bool CreateAnimaSkeletalRigidBodies(UWorld* World, UPackage* MeshesPackage, UPackage* MaterialsPackage, UPackage* AnimPackage);
	bool CreateAnimaOptimizedRigidBodies(UWorld* World, UPackage* MeshesPackage, UPackage* MaterialsPackage, UPackage* AnimationPackage);

	bool CreateAnima4DActors(UWorld* World, UPackage* MeshesPackage, UPackage* MaterialsPackage, UPackage* AnimationPackage);

	AStaticMeshActor* GetStaticMeshActor(UWorld * World, FString ActorName);
	bool RemoveExistingStaticActor(UWorld* World, FString ActorName);
	ASkeletalMeshActor* GetSkeletalMeshActor(UWorld * World, FString ActorName);
	bool RemoveExistingSkeletalActor(UWorld* World, FString ActorName);

	//Track what textures, mesh and materials are used on import
	//TArray<bool> texUsed;
	TArray<bool> MeshUsed;
	TArray<bool> MeshLodRequired;
	TArray<MaterialUsage> MatsUsed;
	TArray<TextureUsage> TexUsed;
	TArray<UStaticMesh*> StaticMeshes;
	TArray<USkeletalMesh*> SkeletalMeshes;
	TArray<UAnimSequence*> SkeletalAnims;
	static bool anima_plugin_initialized;

	UPhysicsAsset* BuildPhysicsAsset(USkeletalMesh* SkeletalMesh, UPackage* Package);
	void CloneStaticMeshWithLods(int id, const Anima::PluginMesh* animaMesh, UStaticMesh* lastMesh, TArray < Anima::PluginMesh*>& animaMeshArray, UPackage* MeshesPackage, UPackage* MaterialsPackage, UPackage* Package, bool forceSaving);

	bool BuildEscalatorSkeletalMesh(Anima::PluginEscalator *Escalator, FSkeletalMeshLODModel& LODModel, const FReferenceSkeleton& RefSkeleton);
	bool BuildRigidbodySkeletalMeshes(Anima::PluginRigidBody* Body, FSkeletalMeshLODModel& LODModel, const FReferenceSkeleton& RefSkeleton);
	bool PostBuildSkeletalMeshFbx(USkeletalMesh* SkeletalMesh);
	bool PostBuildSkeletalMesh(USkeletalMesh* SkeletalMesh, const int32 LODIndex);
	bool InitializeApi();
};

