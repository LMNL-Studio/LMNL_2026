
#pragma once

#include "CoreMinimal.h"
#include <functional>
#include "UObject/Object.h"
#include "Materials/MaterialInterface.h"
#include "Anima4DStreamInfo.generated.h"


USTRUCT(BlueprintType)
struct ANIMA4DUNREALPLUGIN_API FAnima4DStreamPaths {
	GENERATED_BODY()

	// File paths relative to Content
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anima4D")
	FString MeshPath;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anima4D")
	FString VideoPath;


	FAnima4DStreamPaths() {;}

	bool Valid() const;
};

uint32 GetTypeHash(const FAnima4DStreamPaths& StreamPaths);
bool operator==(const FAnima4DStreamPaths& A, const FAnima4DStreamPaths& B);

// Data storing Anima4D information: stream paths per level of detail, 
// Used by Anima4DPlugin to create a uasset file 

UCLASS(BlueprintType)
class ANIMA4DUNREALPLUGIN_API UAnima4DStreamInfo : public UObject
{
	GENERATED_BODY()

public:
	// stores a stream path pair (mesh, video) per level of detail
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anima4D")
		TArray<FAnima4DStreamPaths> StreamPaths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anima4D")
		TSoftObjectPtr<UMaterialInterface> Material; //making it a soft reference skips saving it in package if it is not used

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  category = "Anima4D" )
	FVector OffsetLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Anima4D" )
	FRotator OffsetRotation;

#if WITH_EDITOR
	//  delegates keep a weak reference to the UObject you target 

	// stream paths are 4d stream files that are used by stream players
	// when in use, these files are locked and need to be closed before the operating system allows deleting them 
	// we use the following notification system for this purpose 

	// this delegate is used to notify stream players using this info to close before replacement, lambda that will be called when streams have closed
	typedef std::function<void()> FAnima4DStreamInfoIsReadyToBeReplaced;
	DECLARE_MULTICAST_DELEGATE_OneParam(FAnima4DStreamInfoWillBeReplaced, const FAnima4DStreamInfoIsReadyToBeReplaced& )
	FAnima4DStreamInfoWillBeReplaced StreamInfoWillBeReplaced;

	// this delegate is used to notify stream players using this info to reboot after replacement
	DECLARE_MULTICAST_DELEGATE(FAnima4DStreamInfoWasReplaced)
	FAnima4DStreamInfoWasReplaced StreamInfoWasReplaced;
	
	// this delegate is used to wait for stream players using this info to close streams, lambda that will be called when streams have closed
	typedef std::function<void()> FAnima4DStreamInfoIsReadyToBeDeleted;
	DECLARE_MULTICAST_DELEGATE_OneParam(FAnima4DStreamInfoWasDeleted, const FAnima4DStreamInfoIsReadyToBeDeleted& )
	FAnima4DStreamInfoWasDeleted StreamInfoWasDeleted;


#endif

	UPROPERTY()
		float PlayTimeLimit;

private:
	UPROPERTY()
		TSet<FString> ProjectNames;
//#if WITH_EDITOR
	//void OnAssetRemoved(const FAssetData& AssetData);
	//void AddStreamInfoFilesForDeferredRemove();
//#endif
public:
	UAnima4DStreamInfo();
	~UAnima4DStreamInfo();

	size_t Size() const;	
	void Clear();
	virtual void BeginDestroy();
	virtual void FinishDestroy();
	void UpdateProject();
	bool HasBeenMigrated() const;
};

uint32 GetTypeHash(const UAnima4DStreamInfo& StreamPaths);
bool operator==(const UAnima4DStreamInfo& A, const UAnima4DStreamInfo& B);
