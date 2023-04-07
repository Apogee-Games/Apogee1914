
#include "Widgets/Military/Commanders/CommanderWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Characters/StateMachine/MilitaryControlPawnState.h"
#include "Military/Managers/CommandersManager.h"

void UCommanderWidget::SetCommander(UObject* ProvidedCommander)
{
	Commander = Cast<UPerson>(ProvidedCommander);
}

void UCommanderWidget::RefreshData()
{
	CommanderImage->SetBrushResourceObject(Commander->GetImage());

	AgeTextBlock->SetText(FText::FromString(FString::FromInt(Commander->GetAge())));
	
	NameTextBlock->SetText(FText::FromName(Commander->GetPersonName()));
}

void UCommanderWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UCommanderWidget::OnButtonClick);
}

void UCommanderWidget::OnButtonClick()
{
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	Pawn->SetPawnState(FMilitaryControlPawnState::GetInstance());

	if (ICommandable* Commandable = Pawn->GetSelectedCommandable())
	{
		GetGameInstance()->GetSubsystem<UCommandersManager>()->MakeCommander(Commander, Commandable);
	}
}
