
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
	return GetCountrySpecificLaw(Country->GetId());
}

const TArray<ULawsGroup*>& ULawsManager::GetCountrySpecificLaw(UCountryDescription* CountryDescription)
{
	if (!CountrySpecificLawsGroups.Contains(CountryDescription))
	{
		CountrySpecificLawsGroups.Add(CountryDescription, {});
	}
	return CountrySpecificLawsGroups[CountryDescription];
}

ELoadStage ULawsManager::GetLoadStage()
{
	return ELoadStage::LawsManager;
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
		
		for (const auto& CountryDescription: LawsGroup->CountriesConditions.CountriesTags)
		{
			if (!CountrySpecificLawsGroups.Contains(CountryDescription))
			{
				CountrySpecificLawsGroups.Add(CountryDescription, {});
			}
			CountrySpecificLawsGroups[CountryDescription].Add(LawsGroup);
		}
	}
}