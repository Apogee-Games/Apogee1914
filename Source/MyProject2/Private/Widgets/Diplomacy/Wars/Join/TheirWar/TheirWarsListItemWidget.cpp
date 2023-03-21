#include "Widgets/Diplomacy/Wars/Join/TheirWar/TheirWarsListItemWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"

void UTheirWarsListItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UTheirWarsListItemWidget::OnButtonClick);
}

void UTheirWarsListItemWidget::SetWar(UObject* ProvidedWar)
{
	War = Cast<UWar>(ProvidedWar);
}

void UTheirWarsListItemWidget::RefreshData()
{
	AttackerFlagImage->SetBrushResourceObject(War->GetAttackerLeader()->GetFlag());
	DefenderFlagImage->SetBrushResourceObject(War->GetDefenderLeader()->GetFlag());
	WarNameTextBlock->SetText(FText::FromString(War->GetName()));
}

void UTheirWarsListItemWidget::OnButtonClick()
{
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetTheirWarsListWidget()->SetSelectedWar(War);
}
