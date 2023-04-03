#pragma once
#include "BuildingTypeDescriptionWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/ScrollBox.h"
#include "Economics/Description/Buildings/BuildingDescription.h"

#include "BuildingsTypesListWidget.generated.h"

UCLASS()
class UBuildingsTypesListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UScrollBox* BuildingsDescriptionScrollBox;

	UPROPERTY(EditDefaultsOnly)
	TMap<FName, TSubclassOf<UBuildingTypeDescriptionWidget>> WidgetsClasses;

	void Init(const TArray<UBuildingDescription*>& BuildingDescriptions);
private:
	void AddBuilding(UBuildingDescription* BuildingDescription);
};
