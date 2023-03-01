// Fill out your copyright notice in the Description page of Project Settings.


#include "ProvinceDataWidget.h"

#include "MyProject2/Administration/Instances/State.h"
#include "MyProject2/Administration/Managers/StateManager.h"

void UProvinceDataWidget::SetNewProvince(UProvince* Province)
{
	if(!Province) return;
	
	SetProvinceName(Province->GetName());
	SetPopulationNumber(Province->GetPopulation()->GetPopulation());
	SetResources(Province->GetResources());

	const UState* State = GetWorld()->GetSubsystem<UStateManager>()->GetState(Province->GetStateId());

	if (!State) return;

	SetStateName(State->GetName());
}

void UProvinceDataWidget::SetProvinceName(const FName& ProvinceName) const
{
	ProvinceNameTextBlock->SetText(FText::FromName(ProvinceName));
}

void UProvinceDataWidget::SetPopulationNumber(int32 Population) const
{
	SetPopulationNumber(FText::FromString(FString::FromInt(Population)));
}

void UProvinceDataWidget::SetPopulationNumber(const FText& PopulationNumber) const
{
	PopulationNumberTextBlock->SetText(PopulationNumber);
}

void UProvinceDataWidget::SetStateName(const FName& StateName) const
{
	StateNameTextBlock->SetText(FText::FromName(StateName));
}

void UProvinceDataWidget::SetResources(const TMap<FName, int32>& Resources) const
{
	FString Result = "";
	
	for (const auto& [ResourceName, ResourceCount]: Resources)
	{
		Result += ResourceName.ToString() + ":" + FString::FromInt(ResourceCount) + "\n";
	}
	
	ResourcesTextBlock->SetText(FText::FromString(Result));
}
