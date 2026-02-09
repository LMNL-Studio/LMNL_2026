// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Anima4DMeshComponent.h"
#include "Components/BillboardComponent.h"

#include "Anima4DActor.generated.h"


UCLASS()
class ANIMA4DUNREALPLUGIN_API AAnima4DActor : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USceneComponent* RootSceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UAnima4DMeshComponent* Anima4DMeshComponent;

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UBillboardComponent* AnimaBillboardComponent;

public:
	AAnima4DActor();

	virtual void BeginDestroy() override;
	virtual void FinishDestroy() override;

};
