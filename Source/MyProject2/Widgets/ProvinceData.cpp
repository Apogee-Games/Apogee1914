// Fill out your copyright notice in the Description page of Project Settings.


#include "ProvinceData.h"

void UProvinceData::SetProvinceName(const FString& ProvinceName) const
{
	ProvinceNameTextBlock->SetText(FText::FromString(ProvinceName));
}

void UProvinceData::SetPopulationNumber(const FString& PopulationNumber) const
{
	PopulationNumberTextBlock->SetText(FText::FromString(PopulationNumber));
}

void UProvinceData::SetStateName(const FString& StateName) const
{
	StateNameTextBlock->SetText(FText::FromString(StateName));
}

void UProvinceData::SetResources(const TMap<FString, int>& Resources) const
{
	FString Result = "";
	
	for (const auto& Resource: Resources)
	{
		Result += Resource.Key + ":" + FString::FromInt(Resource.Value) + "\n";
	}
	
	ResourcesTextBlock->SetText(FText::FromString(Result));
}
