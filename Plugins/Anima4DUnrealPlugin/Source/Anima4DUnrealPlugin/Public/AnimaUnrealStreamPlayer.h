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

#include <array>
#include <vector>
#include <map>
#include <memory>
#include <unordered_map>

#include "Math/RandomStream.h"
#include "Engine/Engine.h"
#include "Engine/TextureDefines.h"
#include "Engine/Texture2D.h"
#include "DynamicMeshBuilder.h"

#include "AxyzGPUImage.h"
#include "AxyzStreamPlayer.h"
#include "Anima4DDataSource.h"
#include "AnimaStreamCommon.h"
#include "Anima4DStreamInfo.h"

#include "Tickable.h"
#include "StaticMeshResources.h"
#include "DynamicMeshBuilder.h"

#include "AnimaAutogenProtection.h"
#ifdef ANIMA_PROTECTION_DISABLED
	#define ANIMA4D_DEBUG_MODE true
#else 
	#define ANIMA4D_DEBUG_MODE false
#endif

#include "AnimaUnrealStreamPlayer.generated.h"

#define Anima4DDebugModeCVarName "anima.4d.debug"
#define Anima4DDebugModeLODBiasCVarName "anima.4d.debug.lodbias"

/** Event for stream decoder closing */
class FAnima4DStreamDecoder : public FDeferredCleanupInterface 
{
public:

	// init a decoder with this info, can be hash key in unordered_map and TMap and TSet
	struct PlayInfo {
		UAnima4DStreamInfo* streamInfo;
		AActor* parentActor;
		float phase;
		float timeFactor;
		float timeOffset;

		// for rendering
		ERHIFeatureLevel::Type featureLevel;
		TextureMipGenSettings filtering;

		PlayInfo()
			: streamInfo(nullptr)
			, parentActor(nullptr)
			, phase(0)
			, timeFactor(1)
			, timeOffset(0)
			, featureLevel(ERHIFeatureLevel::SM5)
			, filtering(TextureMipGenSettings::TMGS_SimpleAverage)
		{ ; }

		struct HashFunctor {
			size_t operator()(const PlayInfo& k) const;
		};
	};

	class RenderThreadData : public AxyzStreamPlayer::Listener
	{
	public:
		FStaticMeshVertexBuffers VertexBuffers;
		FDynamicMeshIndexBuffer32 IndexBuffer;
		FLocalVertexFactory VertexFactory;

#if RHI_RAYTRACING
		FRayTracingGeometry RayTracingGeometry;
#endif
		UTexture2D* DiffuseTexture;
		UTexture2D* VelocityTexture;

		TextureMipGenSettings Filtering;
		Anima::StreamQuality Quality;
		Anima::StreamQuality RequestedStreamQuality;
		Anima::StreamQuality MinStreamQuality;

		int CurrentKeyframe;
		int CurrentMeshTimestamp;
		int CurrentImageTimestamp;
		double PreviousFrame;
		size_t MaxVertices = 0;

		FAnima4DStreamDecoder* StreamDecoder;

		bool Visible;

		struct ImageFence {
			FGPUFenceRHIRef Fence;
			bool writeActive;

			ImageFence() {
				Fence = RHICreateGPUFence("ImageFence");
				writeActive = false;
			}

			~ImageFence() {
				Fence.SafeRelease();
			}
		};

		std::map<AxyzStreamReader::Image*, ImageFence> ImageFenceMap;
	public:

		RenderThreadData(ERHIFeatureLevel::Type InFeatureLevel);
		virtual ~RenderThreadData();

		void ReleaseResources();
		void InitResources(FAnima4DStreamDecoder* StreamDecoder);
		void InitRaytracing();
		void SetInitialQuality_RenderThread(Anima::StreamQuality InitialQuality,Anima::StreamQuality MinimumQuality, TextureMipGenSettings Filtering);
		void UpdateSection_RenderThread(double Frame, const AxyzStreamReader::Frame& FrameData);

	private:
		void InitOrUpdateResource(FRenderResource* Resource);

	public:
		// Implements AxyzStreamPlayer::Listener

	private:
		virtual void clearFrame() override; 
		virtual void updateFrame(double frame, const AxyzStreamReader::Frame &frameResult) override;
		virtual bool requiresMeshLocks() override;
		virtual bool requiresImageLocks() override;
		// Implements AxyzStreamPlayer::Listener
	};
	
	class PreloadFactory : public AxyzStreamReader::PreloadFactory {
	public:
		virtual AxyzStreamReader::Image *createImage(const AxyzVideoDecoder *videoDecoder, AxyzImage::Format videoFormat, unsigned mipCount) override;
		virtual void destroyImage(AxyzStreamReader::Image *image) override;
	};
private:
	struct UnrealMeshDecoder {
		FAnima4DDataSource dataSource;
		AxyzIODevice* file;
		AxyzMeshDecoder* decoder;

		UnrealMeshDecoder() :
			file(nullptr),
			decoder(nullptr)
		{
			;
		}

		bool init(const FString& path);
		void destroy();
	};

	struct UnrealVideoDecoder {
		FAnima4DDataSource dataSource;
		AxyzIODevice* file;
		AxyzVideoDecoder* decoder;

		UnrealVideoDecoder() :
			file(nullptr),
			decoder(nullptr)
		{
			;
		}

		bool init(const FString& path);
		void destroy();
	};
public:
	static const int NumMips = 4;
private:
	PlayInfo playInfo;
	double FPS;
	std::vector<UnrealMeshDecoder> MeshDecoders;
	std::vector<UnrealVideoDecoder> VideoDecoders;
	std::unique_ptr<AxyzStreamPlayer> AxyzPlayer;
	PreloadFactory preloadFactory;
	std::unique_ptr<RenderThreadData> RenderData;
	float MaxDeltaTime;

	FRandomStream RandomStream; // used for unique texture names

	// Since these are added to root, they might get Garbage Collected on Editor shutdown, thus we keep weak ptrs
	TWeakObjectPtr<UTexture2D> DiffuseTexture;
	TWeakObjectPtr<UTexture2D> VelocityTexture; // used for WorldPositionOffset (as a way to get motion blur)

public:
	FAnima4DStreamDecoder();
	~FAnima4DStreamDecoder();

	bool Open(const PlayInfo& Info);
	void UpdateTextures(Anima::StreamQuality MaximumQuality);
	void InitRenderResources();
	void ReleaseRenderResources();
	void Close();
	
	const PlayInfo& getPlayInfo() const { return playInfo; }
	double getFPS() const { return FPS; }

	const RenderThreadData* getRenderThreadData() const { return RenderData.get(); }
	RenderThreadData* getRenderThreadData() { return RenderData.get(); }

	const UTexture2D* getDiffuseTexture() const { return DiffuseTexture.Get(); }
	UTexture2D* getDiffuseTexture() { return DiffuseTexture.Get(); }
	const UTexture2D* getVelocityTexture() const { return VelocityTexture.Get(); }
	UTexture2D* getVelocityTexture() { return VelocityTexture.Get(); }

	int getNumFrames() const;

	int getMaxVertex() const;
	int getMaxIndices() const;

	int getMaxDiffuseTextureWidth() const;
	int getMaxDiffuseTextureHeight() const;

	size_t getLODCount() const;
	int getDiffuseTextureWidthForLOD(Anima::StreamQuality quality) const;
	int getDiffuseTextureHeightForLOD(Anima::StreamQuality quality) const;

	FBoxSphereBounds getBoundingBox() const;


	void RequestMeshUpdate_RenderThread_Start(double Time, bool qualitySync);
	void RequestMeshUpdate_RenderThread_End();
private:
	void CreateDiffuseTexture(Anima::StreamQuality MaximumQuality);
	void CreateVelocityTexture();
	void DestroyDiffuseTexture();
	void DestroyVelocityTexture();
	void DestroyDecoders();

	// from UPrimitiveComponent
	//virtual void BeginDestroy() override;
	//virtual void FinishDestroy() override;

public:
	static EPixelFormat GetPixelFormat(int textureEncoding);


	static constexpr EPixelFormat VelocityTextureFormat = EPixelFormat::PF_A32B32G32R32F;

#if WITH_EDITOR

public:
	DECLARE_EVENT(FAnima4DStreamDecoder, FAnima4DStreamDecoderInfoWillBeReplaced );
	FAnima4DStreamDecoderInfoWillBeReplaced Anima4DStreamDecoderInfoWillBeReplaced;
	DECLARE_EVENT(FAnima4DStreamDecoder, FAnima4DStreamDecoderInfoWillBeDeleted);
	FAnima4DStreamDecoderInfoWillBeDeleted Anima4DStreamDecoderInfoWillBeDeleted;
	

private:
	void OnAnima4DStreamInfoAssetWillBeReplaced(const UAnima4DStreamInfo::FAnima4DStreamInfoIsReadyToBeReplaced& StreamInfoIsReadyToBeReplaced);
	UAnima4DStreamInfo::FAnima4DStreamInfoIsReadyToBeReplaced OnStreamInfoIsReadyToBeReplaced;

	void OnAnima4DStreamInfoAssetWasDeleted(const UAnima4DStreamInfo::FAnima4DStreamInfoIsReadyToBeDeleted& StreamInfoIsReadyToBeDeleted);
	UAnima4DStreamInfo::FAnima4DStreamInfoIsReadyToBeDeleted OnStreamInfoIsReadyToBeDeleted;

#endif
};

UCLASS()
class ANIMA4DUNREALPLUGIN_API UAnimaUnrealStreamPlayer : public UObject, public FTickableGameObject {
	GENERATED_BODY()

public:

	typedef TArray< TWeakPtr<FAnima4DStreamDecoder> > FStreamDecoders;

private:
	UWorld* GetCurrentWorld();
	FStreamDecoders StreamDecoders;

	float Time;
	UWorld* World;

#if WITH_EDITOR
	FDelegateHandle EndPIEdelegate;
	FDelegateHandle BeginTickHandle;
	FDelegateHandle PostEditorTickHandle;
#endif
public:

	UAnimaUnrealStreamPlayer();
	virtual ~UAnimaUnrealStreamPlayer();

	TSharedPtr<FAnima4DStreamDecoder> CreateStreamDecoder(const FAnima4DStreamDecoder::PlayInfo& playInfo);

	void Init(UWorld* World);
	void Shutdown();
	void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;
	UWorld* GetWorld() const override;

	void StartUpdateStreamDecoderTime(const TWeakPtr<FAnima4DStreamDecoder>& StreamDecoderWeakPtr, float Time);
	void EndUpdateStreamDecoderTime(const TWeakPtr<FAnima4DStreamDecoder>& StreamDecoderWeakPtr);

private:
#if WITH_EDITOR
	UFUNCTION(Category = "Anima4D")
	void OnPIEEndPlay(const bool dontknow);
#endif
};

uint32 GetTypeHash(const FAnima4DStreamDecoder::PlayInfo& PlayInfo);
bool operator==(const FAnima4DStreamDecoder::PlayInfo& A, const FAnima4DStreamDecoder::PlayInfo& B);
bool operator!=(const FAnima4DStreamDecoder::PlayInfo& A, const FAnima4DStreamDecoder::PlayInfo& B);
