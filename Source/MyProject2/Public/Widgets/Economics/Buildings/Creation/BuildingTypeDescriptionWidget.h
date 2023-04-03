#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Economics/Description/Buildings/BuildingDescription.h"

#include "BuildingTypeDescriptionWidget.generated.h"

UCLASS()
class UBuildingTypeDescriptionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* BuildingNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	virtual void Init(UBuildingDescription* ProvidedBuildingDescription);
protected:
	UPROPERTY()
	UBuildingDescription* BuildingDescription;

	UFUNCTION()
	void OnButtonClick();
};
