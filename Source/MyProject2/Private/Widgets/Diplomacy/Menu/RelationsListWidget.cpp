#include "Widgets/Diplomacy/Menu/RelationsListWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "MyProject2/MyProject2.h"

void URelationsListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FGlobalUIDelegates::OnCountrySelected.AddUObject(this, &ThisClass::OnCountrySelected);
	
	Lists.Add(ERelationType::War, EnemyCountriesListView);
	Lists.Add(ERelationType::NonAggressionPact, NonAggressionPactCountriesListView);
	Lists.Add(ERelationType::DefencivePact, DefencivePactCountriesListView);
	Lists.Add(ERelationType::Allied, AlliedCountriesListView);

	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	OwnerCountry = Pawn->GetRuledCountry();
	OnCountrySelected(Pawn->GetSelectedCountry());
	
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->OnCountryRelationsTypeChanged.AddUObject(this, &ThisClass::OnCountryRelationsTypeChanged);
}

void URelationsListWidget::NativeDestruct()
{
	Super::NativeDestruct();

	FGlobalUIDelegates::OnCountrySelected.RemoveAll(this);

	GetGameInstance()->GetSubsystem<URelationshipsManager>()->OnCountryRelationsTypeChanged.RemoveAll(this);
	
	Lists.Empty();
}

void URelationsListWidget::OnCountryRelationsTypeChanged(UCountry* ProbableOwner, UCountry* ProbableCountry, ERelationType Relation)
{
	if (ProbableOwner == OwnerCountry && ProbableCountry == Country)
	{
		RefreshData();
	}
}

void URelationsListWidget::OnCountrySelected(UCountry* InCountry)
{
	Country = InCountry;
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
