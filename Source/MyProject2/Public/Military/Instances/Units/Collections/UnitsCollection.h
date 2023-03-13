#pragma once
#include "Military/Instances/Units/Collection.h"
#include "UnitsCollection.generated.h"

UCLASS()
class UUnitsCollection: public UObject, public TFCollection<UUnit*>
{
	GENERATED_BODY()
public:
	virtual bool Add(UUnit* Unit) override;
	
	virtual bool Remove(UUnit* Unit) override;
	
	virtual const TArray<UUnit*>& GetAll() const override;
	
	virtual int32 GetSize() const override;
private:
	UPROPERTY()
	TArray<UUnit*> Units;
};
