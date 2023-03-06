#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyProject2/Economics/Instances/Public/Building.h"
#include "ProvinceBuildingWidget.generated.h"

UCLASS()
class UProvinceBuildingWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* BuildingNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LabourTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* MaxLabourTextBlock;

	UFUNCTION(BlueprintCallable)
	void SetBuilding(UObject* ProvidedBuilding);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UBuilding* Building;
};
