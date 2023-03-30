#include "Actions/OutcomeAppliers/NonAlignedOutcomeApplier.h"
#include "Kismet/KismetStringLibrary.h"

FNonAlignedOutcomeApplier::FNonAlignedOutcomeApplier(UCountriesManager* CountriesManager): CountriesManager(CountriesManager)
{
	
}

void FNonAlignedOutcomeApplier::Apply(const TMap<FName, FString>& Values)
{
	UCountry* Country = CountriesManager->GetCountry(FName(Values["Country"]));
	Country->SetIsNonAligned(UKismetStringLibrary::Conv_StringToInt(Values["IsNonAligned"]) != 0);
}
