// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Administration/ProvinceDataWidget.h"

#include "Administration/Instances/State.h"
#include "Administration/Managers/StateManager.h"

void UProvinceDataWidget::SetNewProvince(UProvince* Province)
{
	if (!Province) return;

	ProvinceNameTextBlock->SetText(FText::FromName(Province->GetName()));

	SetPopulationNumber(Province->GetPopulation()->GetPopulation());

	SetResources(Province);

	SetBuildings(Province);

	SetState(Province);

	SetCountries(Province);
}

void UProvinceDataWidget::SetPopulationNumber(int32 Population) const
{
	PopulationNumberTextBlock->SetText(FText::FromString(FString::FromInt(Population)));
}

void UProvinceDataWidget::SetResources(UProvince* Province) const
{
	ResourcesListView->ClearListItems();
	for (const auto& [ResourceName, Resource] : Province->GetResources()->GetMap())
	{
		ResourcesListView->AddItem(Resource);
	}
}

void UProvinceDataWidget::SetBuildings(UProvince* Province) const
{
	BuildingsListView->ClearListItems();
	for (const auto& Building : Province->GetBuildings())
	{
		BuildingsListView->AddItem(Building);
	}
}

void UProvinceDataWidget::SetState(UProvince* Province) const
{
	const UState* State = GetWorld()->GetSubsystem<UStateManager>()->GetState(Province->GetStateId());

	if (State)
	{
		StateNameTextBlock->SetText(FText::FromName(State->GetName()));
	}
	else
	{
		StateNameTextBlock->SetText(FText::FromName(TEXT("None")));
	}
}

void UProvinceDataWidget::SetCountries(UProvince* Province) const
{
	CountryOwnerNameTextBlock->SetText(FText::FromName(Province->GetOwnerCountry()->GetName()));
	CountryOwnerFlagImage->SetBrushResourceObject(Province->GetOwnerCountry()->GetFlag());

	if (Province->GetOwnerCountry() == Province->GetCountryController())
	{
		ControllerCanvasPanel->SetVisibility(ESlateVisibility::Collapsed);
	} else
	{
		ControllerCanvasPanel->SetVisibility(ESlateVisibility::Visible);
		CountryControllerNameTextBlock->SetText(FText::FromName(Province->GetCountryController()->GetName()));
		CountryControllerFlagImage->SetBrushResourceObject(Province->GetCountryController()->GetFlag());
	}
}

