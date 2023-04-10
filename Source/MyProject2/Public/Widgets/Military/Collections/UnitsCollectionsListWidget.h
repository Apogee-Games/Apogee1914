#pragma once
#include "MilitaryBranchUnitsCollectionsListWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/ScrollBox.h"
#include "Military/Interfaces/Observers/UnitCreationObserver.h"
#include "Military/Interfaces/Observers/UnitsCollectionCreationObserver.h"
#include "Military/Interfaces/Observers/UnitsCollectionGroupCreationObserver.h"
#include "Military/Interfaces/Observers/UnitsCollectionGroupRemovalObserver.h"
#include "Military/Interfaces/Observers/UnitsCollectionRemovalObserver.h"
#include "UnitsCollectionsListWidget.generated.h"

UCLASS()
class UUnitsCollectionsListWidget: public UUserWidget, public IUnitsCollectionCreationObserver,
                                   public IUnitsCollectionGroupCreationObserver, public IUnitsCollectionRemovalObserver,
								   public IUnitsCollectionGroupRemovalObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* MilitaryBranchesUnitsCollectionsScrollBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMilitaryBranchUnitsCollectionsListWidget> MilitaryBranchUnitsCollectionsListWidgetClass;

	virtual void NativeConstruct() override;

	virtual void UnitsCollectionIsCreated(UUnitsCollection* UnitsCollection) override;

	virtual void UnitsCollectionGroupIsCreated(UUnitsCollectionGroup* UnitsCollectionGroup) override;
	
	virtual void UnitsCollectionIsRemoved(UUnitsCollection* UnitsCollection) override;

	virtual void UnitsCollectionGroupIsRemoved(UUnitsCollectionGroup* UnitsCollectionGroup) override;

	virtual void NativeDestruct() override;
private:
	UPROPERTY()
	TMap<UMilitaryBranchDescription*, UMilitaryBranchUnitsCollectionsListWidget*> MilitaryBranchUnitsCollectionsListWidget;
};
