#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Military/Descriptions/UnitDescription.h"
#include "UnitTypesListWidget.generated.h"

UCLASS()
class MYPROJECT2_API UUnitTypesListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UListView* UnitDescriptionListView;

	void Init();
private:
	
	void AddUnitType(UUnitDescription* UnitDescription);
};
