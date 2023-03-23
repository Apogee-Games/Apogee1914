#include "Widgets/Diplomacy/Wars/Description/WarDescriptionWidget.h"

void UWarDescriptionWidget::SetWar(UWar* War)
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
