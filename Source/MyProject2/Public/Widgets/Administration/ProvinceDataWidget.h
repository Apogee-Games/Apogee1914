// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Administration/Instances/Province.h"
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
	UListView* ResourcesListView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* BuildingsListView;

	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CountryOwnerNameTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* CountryOwnerFlagImage;

	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* ControllerCanvasPanel;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CountryControllerNameTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* CountryControllerFlagImage;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UFUNCTION()
	void OnProvinceSelected(UProvince* Province);

	void SetPopulationNumber(int32 Population) const;

	void SetResources(UProvince* Province) const;

	void SetBuildings(UProvince* Province) const;

	void SetState(UProvince* Province) const;

	void SetCountries(UProvince* Province) const;
};