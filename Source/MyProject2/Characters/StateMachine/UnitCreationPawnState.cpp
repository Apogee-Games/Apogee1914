#include "UnitCreationPawnState.h"

#include "NoActionPawnState.h"
#include "MyProject2/Maps/Selection/SelectionMap.h"
#include "MyProject2/Characters/HumanPlayerPawn.h"
#include "MyProject2/Military/Managers/UnitsFactory.h"
#include "MyProject2/Utils/LocationUtils.h"


TSharedPtr<FPawnState> FUnitCreationPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FUnitCreationPawnState>(new FUnitCreationPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FUnitCreationPawnState::LeftClick(AHumanPlayerPawn* Pawn)
{
	USelectionMap* SelectionMap = Pawn->GetWorld()->GetSubsystem<USelectionMap>();

	const FVector Point = FLocationUtils::GetNormalizedPositionOnPlane(Pawn);

	UProvince* Province = SelectionMap->SelectProvince(FVector2D(Point.Y, Point.Z));

	UUnitsFactory* UnitsFactory = Pawn->GetWorld()->GetSubsystem<UUnitsFactory>();

	UnitsFactory->Create(Pawn->GetSelectedUnitDescription(), Province, Pawn->GetRuledCountryTag());

	return Instance;
}

TSharedPtr<FPawnState> FUnitCreationPawnState::RightClick(AHumanPlayerPawn* Pawn)
{
	return FNoActionPawnState::GetInstance()->RightClick(Pawn);	
}

bool FUnitCreationPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UUnitTypesListWidget*>(Widget) != nullptr;
}

bool FUnitCreationPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return MustWidgetBeVisible(Widget);
}

FUnitCreationPawnState::FUnitCreationPawnState()
{
}

