#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "MyProject2/Economics/Description/BuildingDescription.h"

#include "BuildingsTypesListWidget.generated.h"

UCLASS()
class UBuildingsTypesListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UListView* BuildingDescriptionListView;

	void AddBuildingType(FBuildingDescription* BuildingDescription);
};
