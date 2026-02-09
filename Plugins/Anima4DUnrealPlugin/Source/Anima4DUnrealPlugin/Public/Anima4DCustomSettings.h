#pragma once

#include "AnimaStreamCommon.h"
#include "Anima4DCustomSettings.generated.h"

/**
 * Setting object used to hold both config settings and editable ones in one place
 * To ensure the settings are saved to the specified config file make sure to add
 * props using the globalconfig or config meta.
 */
UENUM(BlueprintType)
enum class EVideoDecoderDevice : uint8 {
	ECPUDevice = 0       UMETA(DisplayName = "CPU"),
	EGPUDevice1       UMETA(DisplayName = "GPU1"),
	EGPUDevice2       UMETA(DisplayName = "GPU2"),
	EGPUDevice3       UMETA(DisplayName = "GPU3"),
	EGPUDevice4		  UMETA(DisplayName = "GPU4"),
};

UENUM(BlueprintType)
enum class ELodMode4D : uint8 {
	ELodModeAlways = 0				UMETA(DisplayName = "Use LODs Always"),
	ELodModeExcludeCinematic		UMETA(DisplayName = "Do not use LODs in Cinematic"),
	ELodModeNever					UMETA(DisplayName = "Never use LODs")
};

UCLASS(Config = Game, defaultconfig)
class ANIMA4DUNREALPLUGIN_API UAnima4DCustomSettings : public UObject
{
	GENERATED_BODY()

public:
	UAnima4DCustomSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, config, Category = "Anima4D", meta = (Tooltip = "Anima4D characters will skip next keyframe only below this fps threshold (0 to turn off)" ))
	uint32 Minimum4dFPS;

	UPROPERTY(EditAnywhere, config, Category = "Anima4D", meta = (Tooltip = "Choose gpu device for Anima4d decoding" ))
	EVideoDecoderDevice VideoDecoderDevice;

	//UPROPERTY(EditAnywhere, config, Category = anima4D, meta = (Tooltip = "LOD screen view percentage" ))
	float LODScreenPercentages[Anima::StreamQuality::Quality_Level_Count];

	//UPROPERTY(EditAnywhere, config, Category = anima4D, meta = (Tooltip = "Defaults to 0, raise to allow for lower quality LOD (negative numbers may decrease performance)" ))
	int32 LODBias;

	UPROPERTY(EditAnywhere, config, Category = "Anima4D", meta = (Tooltip = "Mipmaps filter Moire patterns in 4D characters. As it is time consuming, used only for final render (Cinematic)"))
	bool CalculateMipmapsForCinematic;
	
	UPROPERTY(EditAnywhere, config, Category = "Anima4D", meta = (Tooltip = "Cinematic mode is only for sequence capture in Anima4D, show warning when selected for viewport" ))
	bool ShowCinematicWarning;

	UPROPERTY(EditAnywhere, config, Category = "Anima4D", meta = (Tooltip = "Defaults to false, setting up to true could have big impact in performance but the highest 4d quality will be used even if you haven't set Cinematic mode"))
	bool AllowMaximum4dQualityWithoutCinematic;

	UPROPERTY(EditAnywhere, config, Category = "Anima4D", meta = (Tooltip = "Select 4D LOD mode (higher quality vs performance)"))
	ELodMode4D LodMode4d;


	/** Sample float property that requires a restart */
	//UPROPERTY(EditAnywhere, config, Category = Anima4D, meta = (ConfigRestartRequired = true))
	//	float SampleFloatRequireRestart;

	///** Sample string list */
	//UPROPERTY(config, EditAnywhere, Category = Anima4D)
	//	TArray<FString> SampleStringList;

	///** Or add min, max or clamp values to the settings */
	//UPROPERTY(config, EditAnywhere, Category = Anima4D, meta = (UIMin = 1, ClampMin = 1))
	//	int32 ClampedIntSetting;

	///** We can even use asset references */
	//UPROPERTY(config, EditAnywhere, Category = Materials, meta = (AllowedClasses = "MaterialInterface"))
	//	FStringAssetReference StringMaterialAssetReference;

};
