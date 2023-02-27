#pragma once

enum class EStorageType : uint8;

class IStorageObserver
{
public:
	virtual ~IStorageObserver() = default;
	virtual void GoodIsUpdated(EStorageType StorageType, const FName& GoodName, int NewAmount) = 0;
};
