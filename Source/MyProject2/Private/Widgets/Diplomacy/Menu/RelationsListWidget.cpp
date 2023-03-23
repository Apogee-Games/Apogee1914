#include "Widgets/Diplomacy/Menu/RelationsListWidget.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void URelationsListWidget::Init()
{
	Lists.Add(War, EnemyCountriesListView);
	Lists.Add(NonAggressionPact, NonAggressionPactCountriesListView);
	Lists.Add(DefencivePact, DefencivePactCountriesListView);
	Lists.Add(Allied, AlliedCountriesListView);
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
		if (Relation == Neutral) continue;
		Lists[Relation]->AddItem(AnotherCountry);
	}
}
