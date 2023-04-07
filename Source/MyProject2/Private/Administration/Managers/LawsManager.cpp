
#include "Administration/Managers/LawsManager.h"

void ULawsManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

const TArray<ULawsGroup*>& ULawsManager::GetCommonLaws() const
{
	return CommonLawsGroups;
}

const TArray<ULawsGroup*>& ULawsManager::GetCountrySpecificLaw(UCountry* Country)
{
	return GetCountrySpecificLaw(Country->GetTag());
}

const TArray<ULawsGroup*>& ULawsManager::GetCountrySpecificLaw(const FName& CountryTag)
{
	if (!CountrySpecificLawsGroups.Contains(CountryTag))
	{
		CountrySpecificLawsGroups.Add(CountryTag, {});
	}
	return CountrySpecificLawsGroups[CountryTag];
}


void ULawsManager::Clear()
{
	CommonLawsGroups.Empty();
	CountrySpecificLawsGroups.Empty();
}

void ULawsManager::Init(UScenario* Scenario)
{
	for (const auto& LawsGroup: Scenario->LawsGroups)
	{
		if (LawsGroup->CountriesConditions.ForAll)
		{
			CommonLawsGroups.Add(LawsGroup);
			continue;
		}
		
		for (const auto& CountryTag: LawsGroup->CountriesConditions.CountriesTags)
		{
			if (!CountrySpecificLawsGroups.Contains(CountryTag))
			{
				CountrySpecificLawsGroups.Add(CountryTag, {});
			}
			CountrySpecificLawsGroups[CountryTag].Add(LawsGroup);
		}
	}
}