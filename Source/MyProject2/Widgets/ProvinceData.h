// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ProvinceData.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UProvinceData : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ProvinceNameTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PopulationNumberTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* StateNameTextBlock;
	

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ResourcesTextBlock;

	void SetProvinceName(const FName& ProvinceName) const;

	void SetPopulationNumber(const FString& PopulationNumber) const;

	void SetStateName(const FName& StateName) const;

	void SetResources(const TMap<FName, int>& Resources) const;
};