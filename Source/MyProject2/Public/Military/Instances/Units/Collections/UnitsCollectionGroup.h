#pragma once
#include "UnitsCollection.h"
#include "Military/Instances/Units/Collection.h"
#include "UnitsCollectionGroup.generated.h"

UCLASS()
class UUnitsCollectionGroup: public UObject, public TFCollection<UUnitsCollection*>
{
	GENERATED_BODY()
public:
	virtual bool Add(UUnitsCollection* Collection) override;
	
	virtual bool Remove(UUnitsCollection* Collection) override;

	virtual const TSet<UUnitsCollection*>& GetAll() const override;

	virtual int32 GetSize() const override;

	virtual bool Contains(UUnitsCollection* Item) override;

private:
	UPROPERTY()
	TSet<UUnitsCollection*> Collections;
};
