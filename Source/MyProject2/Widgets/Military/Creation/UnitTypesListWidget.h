#pragma once
#include "UnitTypeDescriptionWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "MyProject2/Military/Descriptions/UnitDescription.h"
#include "UnitTypesListWidget.generated.h"

UCLASS()
class MYPROJECT2_API UUnitTypesListWidget: public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UGridPanel* ListGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUnitTypeDescriptionWidget> UnitDescriptionWidgetClass;

	void AddUnitType(const FUnitDescription* UnitDescription);

private:
	int Count = 0;
};
