
#include "Widgets/Diplomacy/Wars/List/WarsListWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void UWarsListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->AddWarDeclarationObserver(this);
}

void UWarsListWidget::WarWasDeclared(UWar* War)
{
	UCountry* OwnersCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
	if (War->IsMember(OwnersCountry))
	{
		WarsListView->AddItem(War);
	}
}

void UWarsListWidget::RemoveWar(UWar* War)
{
	WarsListView->RemoveItem(War);
}

void UWarsListWidget::NativeDestruct()
{
	Super::NativeDestruct();
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->RemoveWarDeclarationObserver(this);
}
