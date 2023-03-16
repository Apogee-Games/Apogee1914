#include "Actions/ConditionCheckers/ProvinceControllerChecker.h"

FProvinceControllerConditionChecker::FProvinceControllerConditionChecker(UProvinceManager* ProvinceManager):ProvinceManager(ProvinceManager)
{

}

bool FProvinceControllerConditionChecker::Check(const TMap<FName, FString>& Values)
{
	UProvince* Province = ProvinceManager->GetProvince(FName(*Values["Province"]));
	return Province->GetCountryController()->GetTag() == FName(*Values["Country"]);
}