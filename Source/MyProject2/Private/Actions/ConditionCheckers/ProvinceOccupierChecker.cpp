
#include "Actions/ConditionCheckers/ProvinceOccupierChecker.h"

FProvinceOccupierConditionChecker::FProvinceOccupierConditionChecker(UCountriesManager* CountriesManager, UProvinceManager* ProvinceManager):CountriesManager(CountriesManager),ProvinceManager(ProvinceManager)
{

}

bool FProvinceOccupierConditionChecker::Check(const TMap<FName, FString>& Values)
{
	UProvince* Province = ProvinceManager->GetProvince(FName(*Values['Province']));
	return Province->GetCountryController()->GetTag() == FName(*Values['Country']);
}