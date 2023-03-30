#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "UnitsCollectionsWidget.generated.h"

UCLASS()
class UUnitsCollectionsWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsCollectionsListView;

	bool AddUnitsCollection(UUnitsCollection* UnitsCollection);

	bool RemoveUnitsCollection(UUnitsCollection* UnitsCollection);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	TArray<UUnitsCollection*> UnitsCollections;
};
