#include "Widgets/Diplomacy/Menu/DiplomaticPactsWidgets.h"
#include "Administration/Instances/Country.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "MyProject2/MyProject2.h"


void UDiplomaticPactsWidgets::NativeConstruct()
{
	Super::NativeConstruct();

	FGlobalUIDelegates::OnCountrySelected.AddUObject(this, &ThisClass::OnCountrySelected);
	
	CreateNonAggressionPactButton->OnClicked.AddDynamic(this, &ThisClass::OnCreateNonAggressionPactButtonClick);
	BreakNonAggressionPactButton->OnClicked.AddDynamic(this, &ThisClass::OnBreakNonAggressionPactButtonClick);
	CreateDefencivePactButton->OnClicked.AddDynamic(this, &ThisClass::OnCreateDefencivePactButtonClick);
	BreakDefencivePactButton->OnClicked.AddDynamic(this, &ThisClass::OnBreakDefencivePactButtonClick);

	GetGameInstance()->GetSubsystem<URelationshipsManager>()->OnCountryRelationsTypeChanged.AddUObject(this, &ThisClass::OnCountryRelationsTypeChanged);
	
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	OwnerCountry = Pawn->GetRuledCountry();
	OnCountrySelected(Pawn->GetSelectedCountry());
}

void UDiplomaticPactsWidgets::NativeDestruct()
{
	Super::NativeDestruct();

	FGlobalUIDelegates::OnCountrySelected.RemoveAll(this);

	CreateNonAggressionPactButton->OnClicked.RemoveAll(this);
	BreakNonAggressionPactButton->OnClicked.RemoveAll(this);
	CreateDefencivePactButton->OnClicked.RemoveAll(this);
	BreakDefencivePactButton->OnClicked.RemoveAll(this);
	
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->OnCountryRelationsTypeChanged.RemoveAll(this);
}

void UDiplomaticPactsWidgets::RefreshData()
{
	if (OwnerCountry->HasNonAggressionPactWith(Country)) {
		NonAggressionPactCreationRemovalWidgetSwitcher->SetActiveWidgetIndex(1);
		BreakDefencivePactButton->SetIsEnabled(true); // TODO: Maybe some additional logic here :) ?
	} else
	{
		NonAggressionPactCreationRemovalWidgetSwitcher->SetActiveWidgetIndex(0);
		CreateNonAggressionPactButton->SetIsEnabled(OwnerCountry->CanCreateNonAggressionPactWith(Country));
	}

	if (OwnerCountry->HasDefencivePactWith(Country))
	{
		DefencivePactCreationRemovalWidgetSwitcher->SetActiveWidgetIndex(1);
		BreakDefencivePactButton->SetIsEnabled(true);  // TODO: Maybe some additional logic here :) ?
	} else
	{
		DefencivePactCreationRemovalWidgetSwitcher->SetActiveWidgetIndex(0);
		CreateDefencivePactButton->SetIsEnabled(OwnerCountry->CanCreateDefencivePactWith(Country));
	}
}

void UDiplomaticPactsWidgets::OnCreateNonAggressionPactButtonClick()
{
	OwnerCountry->CreateNonAggressionPactWith(Country);
}

void UDiplomaticPactsWidgets::OnBreakNonAggressionPactButtonClick()
{
	OwnerCountry->BreakNonAggressionPactWith(Country);
}

void UDiplomaticPactsWidgets::OnCreateDefencivePactButtonClick()
{
	OwnerCountry->CreateDefencivePactWith(Country);
}

void UDiplomaticPactsWidgets::OnBreakDefencivePactButtonClick()
{
	OwnerCountry->BreakDefencivePactWith(Country);
}

void UDiplomaticPactsWidgets::OnCountryRelationsTypeChanged(UCountry* ProbableOwner, UCountry* ProbableCountry, ERelationType Relation)
{
	if (ProbableOwner == OwnerCountry && ProbableCountry == Country)
	{
		RefreshData();
	}
}

void UDiplomaticPactsWidgets::OnCountrySelected(UCountry* InCountry)
{
	Country = InCountry;
	RefreshData();
}
