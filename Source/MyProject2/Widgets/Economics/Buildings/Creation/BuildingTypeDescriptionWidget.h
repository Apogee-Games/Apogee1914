#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "MyProject2/Economics/Description/BuildingDescription.h"
#include "MyProject2/Widgets/Economics/Carriers/BuildingDescriptionCarrier.h"

#include "BuildingTypeDescriptionWidget.generated.h"

UCLASS()
class UBuildingTypeDescriptionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* BuildingNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* MaxLaboursTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* GoodsConsumptionListView;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* ResourcesConsumptionListView;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* GoodsProductionListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetCarrier(UObject* ProvidedCarrier);
	
	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	const FBuildingDescription* BuildingDescription;

	UFUNCTION()
	void OnClick();
};
