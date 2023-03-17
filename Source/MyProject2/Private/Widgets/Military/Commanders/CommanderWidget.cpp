﻿
#include "Widgets/Military/Commanders/CommanderWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
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
	Pawn->SetPawnState(FMapBrowsingPawnState::GetInstance());

	if (ICommandable* Commandable = Pawn->GetSelectedCommandable())
	{
		GetWorld()->GetSubsystem<UCommandersManager>()->MakeCommander(Commander, Commandable);
	}
}