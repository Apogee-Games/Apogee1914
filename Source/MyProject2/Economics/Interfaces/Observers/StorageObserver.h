#pragma once

enum class EStorageType : uint8;

class IStorageObserver
{
public:
	virtual ~IStorageObserver() = default;
	virtual void GoodIsUpdated(EStorageType StorageType, UGood* Good) = 0;
};
