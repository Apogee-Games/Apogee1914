#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "Military/Interfaces/Observers/UnitCreationObserver.h"
#include "Military/Interfaces/Observers/UnitsCollectionCreationObserver.h"
#include "Military/Interfaces/Observers/UnitsCollectionGroupCreationObserver.h"
#include "Military/Interfaces/Observers/UnitsCollectionRemovalObserver.h"

#include "UnitsCollectionsWidget.generated.h"

UCLASS()
class UUnitsCollectionsWidget: public UUserWidget, public IUnitsCollectionCreationObserver, public IUnitsCollectionGroupCreationObserver, public IUnitsCollectionRemovalObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* CollectionsGroupsListView;

	virtual void NativeConstruct() override;
	
	virtual void UnitsCollectionIsCreated(UUnitsCollection* UnitsCollection) override;
	
	virtual void UnitsCollectionGroupIsCreated(UUnitsCollectionGroup* UnitsCollectionGroup) override;

	virtual void NativeDestruct() override;
	
	virtual void UnitsCollectionIsRemoved(UUnitsCollection* UnitsCollection) override;
private:
	UPROPERTY()
	TMap<int32, UUnitsCollectionGroup*> DefaultCollectionGroups; // To contain collections that are not in collection group
	// TODO: Should we add just another widget for non units collection group collections
};
