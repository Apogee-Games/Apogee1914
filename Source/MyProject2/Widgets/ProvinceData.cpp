// Fill out your copyright notice in the Description page of Project Settings.


#include "ProvinceData.h"

void UProvinceData::SetProvinceName(const FName& ProvinceName) const
{
	ProvinceNameTextBlock->SetText(FText::FromName(ProvinceName));
}

// TODO: Fix: why not overloading or just numbers :)
void UProvinceData::SetPopulationNumber(const FString& PopulationNumber) const
{
	PopulationNumberTextBlock->SetText(FText::FromString(PopulationNumber));
}

void UProvinceData::SetStateName(const FName& StateName) const
{
	StateNameTextBlock->SetText(FText::FromName(StateName));
}

void UProvinceData::SetResources(const TMap<FName, int>& Resources) const
{
	FString Result = "";
	
	for (const auto& Resource: Resources)
	{
		Result += Resource.Key.ToString() + ":" + FString::FromInt(Resource.Value) + "\n";
	}
	
	ResourcesTextBlock->SetText(FText::FromString(Result));
}
