#pragma once

#include "CoreMinimal.h"
#include "AxyzIO.h"


class FAnima4DDataSource : public AxyzIOSource
{
private:
	FArchive* Reader;
	size_t InitialOffset;
	FString FilePath;
	bool Error;

public:


	FAnima4DDataSource();
	virtual ~FAnima4DDataSource();

	void open(const FString& FilePath, size_t InitialOffset = 0);
	void close();
	bool isOpen() const;
	const FString& getPath() const;

	// Read dataSize bytes into data.
	virtual size_t readData(char *data, size_t dataSize) override;

	// Write dataSize bytes from data.
	virtual size_t writeData(const char *data, size_t dataSize) override;

	// Get the size in bytes of the source.
	virtual long long getSize() override;

	// Get the current offset in the source.
	virtual long long getCurrentOffset() override;

	// Seek to the start of the source.
	virtual void seekStart() override;

	// Seek offset bytes from the current position in the source. Can be positive or negative.
	virtual void seekMove(long long offset) override;

	// Seek to the target offset in the source.
	virtual void seekOffset(long long offset) override;

	// Seek to the end of the source.
	virtual void seekEnd() override;

	// Check whether the source is at the end or not.
	virtual bool atEnd() override;

	// Return whether the source produced an error or not.
	virtual bool hasError() override;


	
};
