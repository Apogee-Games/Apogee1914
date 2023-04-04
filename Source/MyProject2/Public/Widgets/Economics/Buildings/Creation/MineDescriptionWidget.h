#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Economics/Description/Buildings/BuildingDescription.h"
#include "BuildingTypeDescriptionWidget.h"
#include "MineDescriptionWidget.generated.h"

UCLASS()
class UMineDescriptionWidget: public UBuildingTypeDescriptionWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* MaxLaboursTextBlock;

	virtual void Init(UBuildingDescription* ProvidedBuildingDescription) override;
};
