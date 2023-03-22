#include "Widgets/Diplomacy/Menu/DiplomaticPactsWidgets.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void UDiplomaticPactsWidgets::Init()
{
	CreateNonAggressionPactButton->OnClicked.AddDynamic(this, &UDiplomaticPactsWidgets::OnCreateNonAggressionPactButtonClick);
    CreateDefencivePactButton->OnClicked.AddDynamic(this, &UDiplomaticPactsWidgets::OnCreateDefencivePactButtonClick);
	
	OwnerCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
}

void UDiplomaticPactsWidgets::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;
	RefreshData();
}

void UDiplomaticPactsWidgets::RefreshData()
{
	URelationshipsManager* RelationshipsManager = GetGameInstance()->GetSubsystem<URelationshipsManager>();
	CreateNonAggressionPactButton->SetIsEnabled(RelationshipsManager->CanCreateNonAggressionPact(OwnerCountry, Country));
	CreateDefencivePactButton->SetIsEnabled(RelationshipsManager->CanCreateDefencivePact(OwnerCountry, Country));
}

void UDiplomaticPactsWidgets::OnCreateNonAggressionPactButtonClick()
{
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->CreateNonAggressionPact(OwnerCountry, Country);
}

void UDiplomaticPactsWidgets::OnCreateDefencivePactButtonClick()
{
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->CreateDefencivePact(OwnerCountry, Country);
}