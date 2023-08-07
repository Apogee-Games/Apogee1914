#include "Widgets/Economics/Buildings/Production/ProductionListWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Economics/Instances/Buildings/FactoryBuilding.h"
#include "Economics/Managers/BuildingManager.h"

void UProductionListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OwnerCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
	
	UBuildingManager* BuildingManager = GetGameInstance()->GetSubsystem<UBuildingManager>();
	BuildingManager->OnBuildingStatusChanged.AddUObject(this, &ThisClass::OnBuildingStatusChanged);

	FactoriesListView->ClearListItems();
	for (UBuilding* Building: BuildingManager->GetBuildings()) // TODO: Make "get" by country
	{
		if (Building->GetProvince()->GetCountryController() == OwnerCountry)
		{
			FactoriesListView->AddItem(Building);
		}
	}
}

void UProductionListWidget::NativeDestruct()
{
	Super::NativeDestruct();
	GetGameInstance()->GetSubsystem<UBuildingManager>()->OnBuildingStatusChanged.RemoveAll(this);
}

void UProductionListWidget::OnBuildingStatusChanged(UBuilding* Building, EBuildingStatus BuildingStatus)
{
	if (Building->GetClass()->IsChildOf(UFactoryBuilding::StaticClass()) && OwnerCountry == Building->GetCountryController())
	{
		if (BuildingStatus == EBuildingStatus::Constructed)
		{
			FactoriesListView->AddItem(Building);
		}

		if (BuildingStatus == EBuildingStatus::Destroyed)
		{
			FactoriesListView->RemoveItem(Building);
		}
	}
}
