
#include "Actions/ConditionCheckers/ProvinceOwnerChecker.h"

FProvinceOwnerConditionChecker::FProvinceOwnerConditionChecker(UCountriesManager* CountriesManager, UProvinceManager* ProvinceManager):CountriesManager(CountriesManager),ProvinceManager(ProvinceManager)
{

}

bool FProvinceOwnerConditionChecker::Check(const TMap<FName, FString>& Values)
{
	UProvince* Province = ProvinceManager->GetProvince(FName(*Values['Province']));
	return Province->GetOwnerCountry()->GetTag() == FName(*Values['Country']);
}