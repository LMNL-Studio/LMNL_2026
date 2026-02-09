#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AnimaRigidbodyAnimData.h"
#include "AnimaRigidbodyComponent.generated.h"


USTRUCT()
struct FAnimaAnimatableLightMaterial
{
    GENERATED_BODY()

    // Dynamic material we can change at runtime
    UPROPERTY()
    TObjectPtr<UMaterialInstanceDynamic> Material;

    // "Brake", "Turn_L", "Turn_R" ...
    UPROPERTY()
    FName LightTag;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEANIMAASSETS_API UAnimaRigidbodyComponent : public USceneComponent
{
    GENERATED_BODY()

public:    
    UAnimaRigidbodyComponent();

    // Velocidad de reproducción de la animación
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    float PlayRate = 1.0f;

    // Asset de datos que contiene las transformaciones
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TObjectPtr<UAnimaRigidbodyAnimData> AnimData;
    
    // Componentes de Static Mesh que serán animados (must be serialized/duplicated for PIE)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
    TArray<TObjectPtr<UStaticMeshComponent>> TargetComponents;

    // Local pivot offsets (per component) to spin around the intended axle/center
    UPROPERTY(VisibleAnywhere, Category = "Animation")
    TArray<FVector> PivotOffsets;


    UPROPERTY(VisibleAnywhere, Category = "Animation|Lights")
    TArray<FAnimaAnimatableLightMaterial> LightMaterials;

    // Called by the factory (CreateAnimaOptimizedRigidBodies) when it detects a brake/turn light material
    void RegisterLightMaterial(UMaterialInstanceDynamic* DynMat, FName LightTag);

    // helper opcional para que tú mismo fuerces una potencia
    UFUNCTION(BlueprintCallable, Category = "Animation|Lights")
    void SetLightPowerForTag(FName LightTag, float Power);


    UFUNCTION(BlueprintCallable, Category = "Animation")
    void ForceInitialUpdate();

private:
    float CurrentTime = 0.0f;
    void updateFromTick(float DeltaTime);
    
protected:
    virtual void BeginPlay() override;
    virtual void OnRegister() override;
    
public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};