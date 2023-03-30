
#include "Administration/Managers/LawManager.h"

void ULawManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

const TArray<FLawDescription*>& ULawManager::GetCommonLaws() const
{
	return CommonLaws;
}

const TArray<FLawDescription*>& ULawManager::GetCountrySpecificLaw(UCountry* Country)
{
	return GetCountrySpecificLaw(Country->GetTag());
}

const TArray<FLawDescription*>& ULawManager::GetCountrySpecificLaw(const FName& CountryTag)
{
	if (!CountrySpecificLaws.Contains(CountryTag))
	{
		CountrySpecificLaws.Add(CountryTag, {});
	}
	return CountrySpecificLaws[CountryTag];
}


void ULawManager::Clear()
{
	CommonLaws.Empty();
	CountrySpecificLaws.Empty();
}

void ULawManager::Init(UScenario* Scenario)
{
	UDataTable* LawsDescriptionDataTable = Scenario->LawsDescriptionDataTable;
	for (const auto& [Name, Description]: LawsDescriptionDataTable->GetRowMap())
	{
		FLawDescription* CastedDescription = reinterpret_cast<FLawDescription*>(Description);

		if (CastedDescription->CountriesConditions.ForAll)
		{
			CommonLaws.Add(CastedDescription);
			continue;
		}
		
		for (const auto& CountryTag: CastedDescription->CountriesConditions.CountriesTags)
		{
			if (!CountrySpecificLaws.Contains(CountryTag))
			{
				CountrySpecificLaws.Add(CountryTag, {});
			}
			CountrySpecificLaws[CountryTag].Add(CastedDescription);
		}
	}
}