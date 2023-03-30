﻿#include "Widgets/Military/Selection/SelectedUnitsCollectionGroupWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/CommanderSelectionPawnState.h"
#include "Military/Managers/UnitsFactory.h"

void USelectedUnitsCollectionGroupWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &USelectedUnitsCollectionGroupWidget::OnButtonClick);
	RemoveUnitsCollectionGroupButton->OnClicked.AddDynamic(this, &USelectedUnitsCollectionGroupWidget::OnRemoveUnitsCollectionGroupButton);
	CommanderButton->OnClicked.AddDynamic(this, &USelectedUnitsCollectionGroupWidget::OnCommanderButtonClick);
}

void USelectedUnitsCollectionGroupWidget::SetSelectedUnits(UObject* ProvidedUnitsCollectionGroup)
{
	UnitsCollectionGroup = Cast<UUnitsCollectionGroup>(ProvidedUnitsCollectionGroup);
}

void USelectedUnitsCollectionGroupWidget::RefreshData()
{
	UnitsCollectionListView->ClearListItems();
	for (const auto& UnitsCollection: UnitsCollectionGroup->GetAll())
	{
		UnitsCollectionListView->AddItem(UnitsCollection);
	}

	UnitsCollectionNumberTextBlock->SetText(FText::FromString(FString::FromInt(UnitsCollectionGroup->GetSize())));
	
	const FName MilitaryBranchName = MilitaryBranchesNames[static_cast<int>(UnitsCollectionGroup->GetMilitaryBranch())];
	MilitaryBranchTextBlock->SetText(FText::FromName(MilitaryBranchName));

	UPerson* Commander = UnitsCollectionGroup->GetCommander();
	if (Commander)
	{
		CommanderImage->SetBrushResourceObject(Commander->GetImage());
		CommanderNameTextBlock->SetText(FText::FromName(Commander->GetPersonName()));
	} else
	{
		CommanderImage->SetBrushResourceObject(nullptr);
		CommanderNameTextBlock->SetText(FText::FromString(TEXT("None")));
	}
}

void USelectedUnitsCollectionGroupWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnits(UnitsCollectionGroup);
}

void USelectedUnitsCollectionGroupWidget::OnRemoveUnitsCollectionGroupButton()
{
	TArray<UUnitsCollection*> UnitsCollectionsCopy = UnitsCollectionGroup->GetAll().Array();

	GetWorld()->GetSubsystem<UUnitsFactory>()->RemoveUnitCollectionGroup(UnitsCollectionGroup);

	UUnitsSelectionComponent* SelectionComponent = GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent;
	
	SelectionComponent->UnSelectUnits(UnitsCollectionGroup);
	SelectionComponent->SelectUnits(UnitsCollectionGroup, true);
}

void USelectedUnitsCollectionGroupWidget::OnCommanderButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetCommandable(UnitsCollectionGroup);
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FCommanderSelectionPawnState::GetInstance());
}
