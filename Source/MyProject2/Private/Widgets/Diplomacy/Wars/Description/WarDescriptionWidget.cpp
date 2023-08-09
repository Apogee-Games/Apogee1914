#include "Widgets/Diplomacy/Wars/Description/WarDescriptionWidget.h"

#include "Administration/Instances/Country.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "MyProject2/MyProject2.h"

void UWarDescriptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	OnWarSelected(GetOwningPlayerPawn<AHumanPlayerPawn>()->GetSelectedWar());
	
	FGlobalUIDelegates::OnWarSelected.AddUObject(this, &ThisClass::OnWarSelected);
}

void UWarDescriptionWidget::NativeDestruct()
{
	Super::NativeDestruct();

	FGlobalUIDelegates::OnWarSelected.RemoveAll(this);
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
