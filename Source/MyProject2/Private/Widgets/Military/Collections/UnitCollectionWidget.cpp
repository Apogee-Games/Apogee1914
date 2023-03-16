#include "Widgets/Military/Collections/UnitCollectionWidget.h"

#include "Characters/HumanPlayerPawn.h"
#include "Characters/StateMachine/CommanderSelectionPawnState.h"

void UUnitCollectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UUnitCollectionWidget::OnButtonClick);
	CommanderButton->OnClicked.AddDynamic(this, &UUnitCollectionWidget::OnCommanderButtonClick);
}

void UUnitCollectionWidget::SetUnitCollection(UObject* ProvidedUnitsCollection)
{
	UnitsCollection = Cast<UUnitsCollection>(ProvidedUnitsCollection);
}

void UUnitCollectionWidget::RefreshData()
{
	CollectionSizeTextBlock->SetText(FText::FromString(FString::FromInt(UnitsCollection->GetSize())));
	
	const UPerson* Commander = UnitsCollection->GetCommander();
	
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

void UUnitCollectionWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnits(UnitsCollection);
}

void UUnitCollectionWidget::OnCommanderButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetCommandable(UnitsCollection);
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FCommanderSelectionPawnState::GetInstance());
}
