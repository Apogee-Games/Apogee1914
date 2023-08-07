#include "Widgets/Diplomacy/Wars/Description/WarDescriptionWidget.h"

#include "Administration/Instances/Country.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void UWarDescriptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	Pawn->OnWarSelected.AddUObject(this, &ThisClass::OnWarSelected);
}

void UWarDescriptionWidget::NativeDestruct()
{
	Super::NativeDestruct();

	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	Pawn->OnWarSelected.RemoveAll(this);
}

void UWarDescriptionWidget::OnWarSelected(UWar* War)
{
	WarNameTextBlock->SetText(FText::FromString(War->GetName()));

	DefendersListView->ClearListItems();
	AttackersListView->ClearListItems();
	
	for (const auto& Defender: War->GetDefenders())
	{
		DefendersListView->AddItem(Defender);
	}

	for (const auto& Attacker: War->GetAttackers())
	{
		AttackersListView->AddItem(Attacker);
	}
}
