#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "UnitCollectionGroupWidget.generated.h"

UCLASS()
class UUnitCollectionGroupWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* MilitaryBranchTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CollectionGroupSizeTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsCollectionsListView;

	UFUNCTION(BlueprintCallable)
	void SetUnitsCollectionGroup(UObject* ProvidedUnitsCollectionGroup);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UUnitsCollectionGroup* UnitsCollectionGroup; 
};
