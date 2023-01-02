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
