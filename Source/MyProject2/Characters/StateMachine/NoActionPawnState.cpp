#include "NoActionPawnState.h"
#include "MyProject2/Characters/HumanPlayerPawn.h"

#include "MyProject2/Administration/Instances/State.h"
#include "MyProject2/Administration/Managers/StateManager.h"
#include "MyProject2/Maps/Selection/SelectionMap.h"
#include "MyProject2/Utils/LocationUtils.h"

TSharedPtr<FPawnState> FNoActionPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FNoActionPawnState>(new FNoActionPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FNoActionPawnState::LeftClick(AHumanPlayerPawn* Pawn)
{
	USelectionMap* SelectionMap = Pawn->GetWorld()->GetSubsystem<USelectionMap>();

	const FVector Point = FLocationUtils::GetNormalizedPositionOnPlane(Pawn);

	UProvince* Province = SelectionMap->SelectProvince(FVector2D(Point.Y, Point.Z));

	if (Province)
	{
		const UProvinceDataWidget* ProvinceDataWidget = Pawn->GetProvinceDataWidget();
		
		ProvinceDataWidget->SetProvinceName(Province->GetName());
		ProvinceDataWidget->SetPopulationNumber(Province->GetPopulation()->GetPopulation());
		ProvinceDataWidget->SetResources(Province->GetResources());

		const UState* State = Pawn->GetWorld()->GetSubsystem<UStateManager>()->GetState(Province->GetStateId());

		if (State)
		{
			ProvinceDataWidget->SetStateName(State->GetName());
		}
	}

	Pawn->ClearSelectedUnits();
	
	return Instance;
}

TSharedPtr<FPawnState> FNoActionPawnState::RightClick(AHumanPlayerPawn* Pawn)
{
	return Instance;
}

FNoActionPawnState::FNoActionPawnState()
{
}
