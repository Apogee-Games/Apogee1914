#include "Widgets/Diplomacy/Menu/RelationsListWidget.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void URelationsListWidget::Init()
{
	Lists.Add(ERelationType::War, EnemyCountriesListView);
	Lists.Add(ERelationType::NonAggressionPact, NonAggressionPactCountriesListView);
	Lists.Add(ERelationType::DefencivePact, DefencivePactCountriesListView);
	Lists.Add(ERelationType::Allied, AlliedCountriesListView);
}

void URelationsListWidget::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;
	RefreshData();
}

void URelationsListWidget::RefreshData()
{
	for (const auto& [Relation, List] : Lists)
	{
		List->ClearListItems();
	}

	for (const auto& [AnotherCountry, Relation] : Country->GetRelations())
	{
		if (Relation == ERelationType::Neutral) continue;
		Lists[Relation]->AddItem(AnotherCountry);
	}
}
