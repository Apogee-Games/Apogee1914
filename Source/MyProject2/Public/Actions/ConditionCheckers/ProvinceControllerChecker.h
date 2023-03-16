
#pragma once
#include "ConditionChecker.h"
#include "MyGameState.h"
#include "MyProject2/Public/Administration/Managers/ProvinceManager.h"



class FProvinceControllerConditionChecker: public FConditionChecker
{
public:
	FProvinceControllerConditionChecker(UProvinceManager* ProvinceManager);
	
	virtual bool Check(const TMap<FName, FString>& Values) override;
private:
	UProvinceManager* ProvinceManager;	
};
