#include "Actions/ConditionCheckers/NonAlignmentConditionChecker.h"

#include "Kismet/KismetStringLibrary.h"

FNonAlignmentConditionChecker::FNonAlignmentConditionChecker(UCountriesManager* CountriesManager): CountriesManager(CountriesManager)
{
}

bool FNonAlignmentConditionChecker::Check(const TMap<FName, FString>& Values)
{
	UCountry* Country = CountriesManager->GetCountry(FName(Values["Country"]));
	return Country->IsNonAligned() == (UKismetStringLibrary::Conv_StringToInt(Values["IsNonAligned"]) != 0);
}
