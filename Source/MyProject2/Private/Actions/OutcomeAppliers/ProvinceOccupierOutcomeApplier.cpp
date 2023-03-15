
#include "Actions/OutcomeAppliers/ProvinceOccupierOutcomeApplier.h"

FProvinceOccupierOutcomeApplier::FProvinceOccupierOutcomeApplier(UCountriesManager* CountriesManager, UProvinceManager* ProvinceManager): CountriesManager(CountriesManager),ProvinceManager(ProvinceManager)
{
 
}


void FProvinceOccupierOutcomeApplier::Apply(const TMap<FName, FString>& Values)
{
	UCountry* Country = CountriesManager->GetCountry(FName(*Values['Country']));
	UProvince* Province = ProvinceManager->GetProvince(FName(*Values['Province']));

	Province->Conquer(Country);
}