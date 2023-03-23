#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/WarDescriptionBrowsingPawnState.h"
#include "Widgets/Diplomacy/Wars/List/WarsListItemWidget.h"

void UWarsListItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UWarsListItemWidget::OnButtonClick);
}

void UWarsListItemWidget::SetWar(UObject* ProvidedWar)
{
	War = Cast<UWar>(ProvidedWar);
}

void UWarsListItemWidget::RefreshData()
{
	AttackerFlagImage->SetBrushResourceObject(War->GetAttackerLeader()->GetFlag());
	DefenderFlagImage->SetBrushResourceObject(War->GetDefenderLeader()->GetFlag());
}

void UWarsListItemWidget::OnButtonClick()
{
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	Pawn->SetPawnState(FWarDescriptionBrowsingPawnState::GetInstance());
	Pawn->GetController<APlayerController>()->GetHUD<AHumanPlayerHUD>()->GetWarDescriptionWidget()->SetWar(War);
}