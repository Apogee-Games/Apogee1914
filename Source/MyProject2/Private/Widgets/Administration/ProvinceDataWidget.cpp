// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Administration/ProvinceDataWidget.h"

#include "Administration/Instances/Country.h"
#include "Administration/Instances/State.h"
#include "Administration/Managers/StateManager.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "MyProject2/MyProject2.h"

void UProvinceDataWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FGlobalUIDelegates::OnProvinceSelected.AddUObject(this, &ThisClass::OnProvinceSelected);
	OnProvinceSelected(GetOwningPlayerPawn<AHumanPlayerPawn>()->GetSelectedProvince());
}

void UProvinceDataWidget::NativeDestruct()
{
	Super::NativeDestruct();
	FGlobalUIDelegates::OnProvinceSelected.RemoveAll(this);
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
	const UState* State = GetWorld()->GetGameInstance()->GetSubsystem<UStateManager>()->GetState(Province->GetState());

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
	CountryOwnerNameTextBlock->SetText(Province->GetOwnerCountry()->GetName());
	CountryOwnerFlagImage->SetBrushResourceObject(Province->GetOwnerCountry()->GetFlag());

	if (Province->GetOwnerCountry() == Province->GetCountryController())
	{
		ControllerCanvasPanel->SetVisibility(ESlateVisibility::Collapsed);
	} else
	{
		ControllerCanvasPanel->SetVisibility(ESlateVisibility::Visible);
		CountryControllerNameTextBlock->SetText(Province->GetCountryController()->GetName());
		CountryControllerFlagImage->SetBrushResourceObject(Province->GetCountryController()->GetFlag());
	}
}

void UProvinceDataWidget::OnProvinceSelected(UProvince* Province)
{
	if (!Province) return;

	ProvinceNameTextBlock->SetText(Province->GetName());

	SetPopulationNumber(Province->GetPopulation()->GetPopulation());

	SetResources(Province);

	SetBuildings(Province);

	SetState(Province);

	SetCountries(Province);
}
