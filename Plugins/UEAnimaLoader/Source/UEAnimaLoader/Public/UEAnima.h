// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#pragma once  

#define DLL_EXPORT __declspec(dllexport)	//shortens __declspec(dllexport) to DLL_EXPORT

#ifdef __cplusplus		//if C++ is used convert it to C to prevent C++'s name mangling of method names
extern "C"
{
#endif

	bool DLL_EXPORT ImportAnimaScene(UWorld* World, UPackage* Package, const FString actualFilePath, FScopedSlowTask *Progress);
	bool DLL_EXPORT OpenAnimaGallery(UWorld* World, UPackage* Package);
	bool DLL_EXPORT OpenAnimaGalleryDrop(UWorld* World, UPackage* Package);
	bool DLL_EXPORT ForceImportYAsset(UWorld* World, UPackage* Package, TArray<FString> paths, TArray<FString> names, const bool ignoreRiggedAnd4D);

#ifdef __cplusplus
}
#endif