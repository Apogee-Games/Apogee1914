// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyProject2/Administration/Instances/Province.h"
#include "ProvinceDataWidget.generated.h"

UCLASS()
class MYPROJECT2_API UProvinceDataWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ProvinceNameTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PopulationNumberTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StateNameTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ResourcesTextBlock;

	void SetNewProvince(UProvince* Province);
private:
	void SetProvinceName(const FName& ProvinceName) const;

	void SetPopulationNumber(int32 Population) const;
	
	void SetPopulationNumber(const FText& PopulationNumber) const;

	void SetStateName(const FName& StateName) const;

	void SetResources(const TMap<FName, int>& Resources) const;
};