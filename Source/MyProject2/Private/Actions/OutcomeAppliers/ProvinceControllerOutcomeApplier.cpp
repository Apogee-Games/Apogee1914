
#include "Actions/OutcomeAppliers/ProvinceControllerOutcomeApplier.h"

FProvinceControllerOutcomeApplier::FProvinceControllerOutcomeApplier(UCountriesManager* CountriesManager, UProvinceManager* ProvinceManager): CountriesManager(CountriesManager),ProvinceManager(ProvinceManager)
{
 
}


void FProvinceControllerOutcomeApplier::Apply(const TMap<FName, FString>& Values)
{
//	UCountry* Country = CountriesManager->GetCountry(FName(*Values["Country"]));
//	UProvince* Province = ProvinceManager->GetProvince(FName(*Values["Province"]));

//	Province->Conquer(Country);
}