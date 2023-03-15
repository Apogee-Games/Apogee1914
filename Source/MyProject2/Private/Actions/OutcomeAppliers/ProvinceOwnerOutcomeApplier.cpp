
#include "Actions/OutcomeAppliers/ProvinceOwnerOutcomeApplier.h"

FProvinceOwnerOutcomeApplier::FProvinceOwnerOutcomeApplier(UCountriesManager* CountriesManager, UProvinceManager* ProvinceManager): CountriesManager(CountriesManager),ProvinceManager(ProvinceManager)
{
 
}


void FProvinceOwnerOutcomeApplier::Apply(const TMap<FName, FString>& Values)
{
	UCountry* Country = CountriesManager->GetCountry(FName(*Values['Country']));
	UProvince* Province = ProvinceManager->GetProvince(FName(*Values['Province']));

	Province->TakeControl(Country);
}