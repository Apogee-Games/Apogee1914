#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "UnitCollectionWidget.generated.h"

UCLASS()
class UUnitCollectionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CollectionSizeTextBlock;

	UFUNCTION(BlueprintCallable)
	void SetUnitCollection(UObject* ProvidedUnitsCollection);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UUnitsCollection* UnitsCollection;
};
