
#include "Widgets/Diplomacy/Wars/List/WarsListWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Diplomacy/Instances/War.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void UWarsListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->OnWarStatusChanged.AddUObject(this, &ThisClass::OnWarStatusChanged);
}


void UWarsListWidget::NativeDestruct()
{
	Super::NativeDestruct();
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->OnWarStatusChanged.RemoveAll(this);
}

void UWarsListWidget::OnWarStatusChanged(UWar* War, EWarStatus WarStatus)
{
	if (WarStatus == EWarStatus::Declared)
	{
		UCountry* OwnersCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
		if (War->IsMember(OwnersCountry))
		{
			WarsListView->AddItem(War);
		}
	}
	
	if (WarStatus == EWarStatus::Ended)
	{
		UCountry* OwnersCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
		if (War->IsMember(OwnersCountry))
		{
			WarsListView->RemoveItem(War);
		}
	}
}
