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

//#define STATIC_LIB_4DS

#include "CoreMinimal.h"
#include <memory>
#include "UObject/ObjectMacros.h"
#include "DynamicMeshBuilder.h"
#include "Components/MeshComponent.h"

#if WITH_EDITOR
#include "Editor/UnrealEd/Public/Editor.h"
#endif

#include "./Runtime/Launch/Resources/Version.h"

#include "Scalability.h"

//#include "Math/RandomStream.h"

#include "AxyzStreamReader.h"
#include "AnimaUnrealStreamPlayer.h"
#include "Anima4DStreamInfo.h"
#include "Engine/TextureDefines.h"
#include "Delegates/IDelegateInstance.h"

#include "Anima4DMeshComponent.generated.h"


class FPrimitiveSceneProxy;
class FAnima4DMeshSceneProxy;

class USinglePlayerContext {
	TMap<const UWorld*, UAnimaUnrealStreamPlayer* > PlayerPerWorld;
	FDelegateHandle OnExitHandle;
	FDelegateHandle OnPostWorldCleanupHandle;
public:
	USinglePlayerContext();
	~USinglePlayerContext();

	void OnExitEvent();
	void OnWorldCleanupEvent(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources);
	UAnimaUnrealStreamPlayer* GetPlayerForWorld(UWorld* World);

#if WITH_EDITOR
	void OnAssetRemoved(const FAssetData& AssetData);

#endif
};

/**
 *	Component that allows you to use Anima4D meshes 
 */
UCLASS(hidecategories = (Object, LOD, Physics, Collision), editinlinenew, meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class ANIMA4DUNREALPLUGIN_API UAnima4DMeshComponent : public UMeshComponent{
    GENERATED_UCLASS_BODY()
	friend class FAnima4DMeshSceneProxy;

public:

	static FString DynamicDiffuseTextureObjectName;
	static FString DynamicVelocityTextureObjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anima4D",meta = (ToolTip = "Anima4D stream UE asset"))
	UAnima4DStreamInfo* Anima4DStream;	

	UPROPERTY(EditAnywhere, Category = "Anima4D", meta = (ToolTip = "Initial phase in seconds"))
	float Phase;
	
	UPROPERTY(EditAnywhere, Category = "Anima4D", meta = (ToolTip = "Time factor"))
	float TimeFactor;

	static const uint64 ScalabilityMessageId = 4;
	
	enum EVertexTexture {PreviousVertexTexture = 0, CurrentVertexTexture, SizeVertexTexture};

private:

	static std::unique_ptr<USinglePlayerContext> SinglePlayerContextInstance;

    /** Local space bounds of mesh */
    UPROPERTY()
    FBoxSphereBounds LocalBounds;
	

	FRandomStream RandomStream; // used for unique texture names
	UMaterialInstanceDynamic* DynamicMaterialInstance;
	TSharedPtr<FAnima4DStreamDecoder> StreamDecoder;

	float Duration;
	float TimeOffset;

	Anima::StreamQuality ViewportMaxQuality;
	uint32 LODBias;
	bool IsLodSystemEnabled;

	FAnima4DStreamDecoder::PlayInfo PlayInfo;

#if WITH_EDITOR
	
	DECLARE_MULTICAST_DELEGATE(FScalabilityTextureSettingDelegate)
	static FScalabilityTextureSettingDelegate ScalabilityTextureSettingDelegate;

	bool ShouldDisableRegister;
	bool IsRegistrationEnabled;

#endif

private:
#if WITH_EDITOR
	UFUNCTION()
	void Anima4DStreamInfoAssetWillBeReplaced();
	UFUNCTION()
	void Anima4DStreamInfoAssetWasReplaced();
	UFUNCTION()
	void Anima4DStreamInfoAssetWillBeDeleted();
#endif
	
	UFUNCTION(BlueprintCallable, Category = "Anima4D")
		void SetPhase(float value);
	UFUNCTION(BlueprintCallable, Category = "Anima4D")
		void SetTimeFactor(float value);		
	UFUNCTION(BlueprintCallable, Category = "Anima4D")
		void ResetAnimation(float OffsetInSeconds);
	UFUNCTION(BlueprintCallable, Category = "Anima4D")
		float GetDuration();
public:
	~UAnima4DMeshComponent();

	static USinglePlayerContext* GetPlayerContext();

#if WITH_EDITOR
	//Called when a property on this object has been modified externally
	virtual void PreEditChange(FProperty* PropertyThatWillChange) override;
	virtual bool CanEditChange(const FProperty* InProperty) const override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	//virtual void PostInitProperties() override;
	//virtual void PostLoad() override;
	//virtual void OnComponentCreated() override;


	bool IsStreamReady(); 
	float GetDuration() const; 

#if WITH_EDITOR
	UFUNCTION()
	void ScalabilityTextureSettingDidChange();
#endif
private:

	virtual void OnRegister() override;
	virtual void OnUnregister() override;

	virtual void DestroyRenderState_Concurrent() override;
    virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	virtual void CreateRenderState_Concurrent(FRegisterComponentContext* Context);
    
	virtual void BeginDestroy() override;
	virtual void FinishDestroy() override;
	
	//USceneComponent Interface.
    virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
    
    //UMeshComponent Interface.
    virtual int32 GetNumMaterials() const override;

private:

	bool CreateReader();
	void DestroyReader();
	
#if WITH_EDITOR
	void DestroyPlayerRenderSync();

#endif
 
#if WITH_EDITOR
    /** Update LocalBounds member from the local box of each section */
    void UpdateLocalBounds();
#endif
};


