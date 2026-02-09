
#pragma once

#include "Factories/Factory.h"
#include "EditorReimportHandler.h"
#include "Anima4DStreamInfoFactory.generated.h"


UCLASS(HideCategories = Object)
class ANIMA4DUNREALASSET_API UAnima4DStreamInfoFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
	//GENERATED_BODY()

public:
	//~ Begin UObject Interface
	void PostInitProperties();
	//~ End UObject Interface

	//~ Begin UFactory Interface
	virtual FText GetDisplayName() const override;
	virtual bool DoesSupportClass(UClass * Class) override;
	virtual UClass* ResolveSupportedClass() override;
//	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
	//virtual UObject * FactoryCreateBinary(UClass * InClass, UObject * InParent, FName InName, EObjectFlags Flags, UObject * Context, const TCHAR * Type, const uint8 *& Buffer, const uint8 * BufferEnd, FFeedbackContext * Warn);
	//~ End UFactory Interface
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

	//~ Begin FReimportHandler Interface
/*	virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
	virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;
	virtual EReimportResult::Type Reimport(UObject* Obj) override;

//	void ShowImportOptionsWindow(TSharedPtr<SAlembicImportOptions>& Options, FString FilePath, const FAbcImporter& Importer);

	virtual int32 GetPriority() const override;
*/	//~ End FReimportHandler Interface
};
