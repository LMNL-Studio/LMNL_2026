// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Anima4DMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Anima4DLocomotionActor.generated.h"


UCLASS()
class ANIMA4DUNREALPLUGIN_API AAnima4DLocomotionActor : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UAnima4DMeshComponent* Anima4DMeshComponent;

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UBillboardComponent* AnimaBillboardComponent;

public:
	AAnima4DLocomotionActor();

	virtual void BeginDestroy() override;
	virtual void FinishDestroy() override;

};
