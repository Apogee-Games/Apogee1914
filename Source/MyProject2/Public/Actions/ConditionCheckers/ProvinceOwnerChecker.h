#pragma once
#include "ConditionChecker.h"
#include "MyProject2/Public/Administration/Managers/ProvinceManager.h"

class FProvinceOwnerConditionChecker: public FConditionChecker
{
public:
	FProvinceOwnerConditionChecker(UProvinceManager* ProvinceManager);

	virtual bool Check(const TMap<FName, FString>& Values) override;
private:
	UProvinceManager* ProvinceManager;
};
