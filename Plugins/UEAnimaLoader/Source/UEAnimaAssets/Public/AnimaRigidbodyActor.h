#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnimaRigidbodyComponent.h"
#include "AnimaRigidbodyActor.generated.h"

// This actor replaces the old ASkeletalMeshActor for rigid bodies.
// It contains a UAnimaRigidbodyComponent to handle tick-based animation
// and multiple UStaticMeshComponents as children (the rigid body parts).
UCLASS()
class UEANIMAASSETS_API ARigidBodyActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ARigidBodyActor();

    // Root component (needed for the Unreal actor hierarchy).
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anima Rigidbody")
    TObjectPtr<USceneComponent> RootScene;

    // Custom component that handles the animation logic and contains the static meshes.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anima Rigidbody")
    TObjectPtr<UAnimaRigidbodyComponent> RigidbodyComponent;

protected:
    virtual void BeginPlay() override;
};
