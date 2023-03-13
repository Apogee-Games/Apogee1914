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

	virtual const TArray<UUnitsCollection*>& GetAll() const override;

	virtual int32 GetSize() const override;

private:
	UPROPERTY()
	TArray<UUnitsCollection*> Collections;
};
