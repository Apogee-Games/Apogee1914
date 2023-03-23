#include "Administration/Managers/IdeologyManager.h"
#include "WorldPartition/DataLayer/DataLayer.h"

void UIdeologyManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

UIdeology* UIdeologyManager::GetIdeology(const FName& IdeologyTag)
{
	return IdeologiesMap[IdeologyTag];
}

 void UIdeologyManager::Clear()
{
	IdeologiesMap.Empty();
}

void UIdeologyManager::Init(UScenario* Scenario)
{
	UDataTable* IdeologyDescriptionDataTable = Scenario->IdeologyDescriptionsDataTable;

	for (const auto& [Tag, Description]: IdeologyDescriptionDataTable->GetRowMap())
	{
		UIdeology* Ideology = NewObject<UIdeology>(this);
		Ideology->Init(reinterpret_cast<FIdeologyDescription*>(Description));
		IdeologiesMap.Add(Tag, Ideology);
	}
}
