#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "AnimaRigidbodyAnimData.generated.h"



// Struct to store the position, rotation, and scale of a rigid component in one frame.
USTRUCT(BlueprintType)
struct FAnimaRigidbodyFrame
{
    GENERATED_BODY()

    UPROPERTY()
    FVector Position = FVector(1.0f);

    UPROPERTY()
    FQuat Rotation = FQuat(0.0f, 0.0f, 0.0f, 1.0f);

    UPROPERTY()
    FVector Scale = FVector(1.0f);
};

// Struct to store the complete animation data for a single rigid component (all frames).
USTRUCT(BlueprintType)
struct FAnimaRigidbodyComponentData
{
    GENERATED_BODY()

    // Name of the rigid component for binding
    UPROPERTY()
    FName ComponentName;

    // List of animation frames
    UPROPERTY()
    TArray<FAnimaRigidbodyFrame> Frames;
};


// Struct to store the light value changes
USTRUCT(BlueprintType)
struct FAnimaRigidbodyLightTrack
{
    GENERATED_BODY()

    // Brake | Turn_L | Turn_R
    UPROPERTY()
    FName LightTag;

    // One key per frame, same sampling as other tracks
    UPROPERTY()
    TArray<float> LightPowerKeys;
};


UCLASS(BlueprintType)
class UEANIMAASSETS_API UAnimaRigidbodyAnimData : public UDataAsset
{
    GENERATED_BODY()

public:
    // Frame rate of the sampled data (FPS), should be 30.0f
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anima Animation")
    float FrameRate = 30.0f;

    // Total duration of the sequence
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anima Animation")
    float SequenceLength = 0.0f;

    // Animation data for the parent
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anima Animation")
    TArray<FAnimaRigidbodyFrame> RootFrames;

    // Animation data for each rigid body component
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anima Animation")
    TArray<FAnimaRigidbodyComponentData> ComponentTracks;


    // Animation data for lights
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anima Animation")
    TArray<FAnimaRigidbodyLightTrack> LightTracks;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(FPrimaryAssetType("AnimaRigidBodyData"), GetFName());
    }
};