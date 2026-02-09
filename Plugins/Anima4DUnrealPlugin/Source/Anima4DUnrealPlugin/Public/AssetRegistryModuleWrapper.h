#pragma once

#include "UEVersionCompare.h"

#if ENGINE_VERSION_AT_LEAST(5,1)
#	include "AssetRegistry/AssetRegistryModule.h"
#else
#	include "AssetRegistryModule.h"
#endif

inline void AssetRegistryGetAssetsByClassWrapper(FAssetRegistryModule &AssetRegistryModule, UClass *Class, TArray<FAssetData> &OutAssetData, bool bSearchSubClasses = false) {
#if ENGINE_VERSION_AT_LEAST(5,1)
	AssetRegistryModule.Get().GetAssetsByClass(Class->GetClassPathName(), OutAssetData, bSearchSubClasses);
#else
	AssetRegistryModule.Get().GetAssetsByClass(Class->GetFName(), OutAssetData, bSearchSubClasses);
#endif
}