#include "Widgets/Diplomacy/Wars/Join/OurWar/OurWarsListItemWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"

void UOurWarsListItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UOurWarsListItemWidget::OnButtonClick);
}

void UOurWarsListItemWidget::SetWar(UObject* ProvidedWar)
{
	War = Cast<UWar>(ProvidedWar);
}

void UOurWarsListItemWidget::RefreshData()
{
	AttackerFlagImage->SetBrushResourceObject(War->GetAttackerLeader()->GetFlag());
	DefenderFlagImage->SetBrushResourceObject(War->GetDefenderLeader()->GetFlag());
	WarNameTextBlock->SetText(FText::FromString(War->GetName()));
}

void UOurWarsListItemWidget::OnButtonClick()
{
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetOurWarsListWidget()->SetSelectedWar(War);
}
