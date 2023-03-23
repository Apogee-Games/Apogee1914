#pragma once
#include "Military/Instances/Units/Collection.h"
#include "Military/Interfaces/Commandable.h"
#include "UnitsCollection.generated.h"

UCLASS()
class UUnitsCollection: public UObject, public TFMilitaryCollection<UUnit*>, public ICommandable
{
	GENERATED_BODY()
public:
	virtual bool Add(UUnit* Unit) override;
	
	virtual bool Remove(UUnit* Unit) override;
	
	virtual const TSet<UUnit*>& GetAll() const override;
	
	virtual int32 GetSize() const override;

	virtual bool Contains(UUnit* Unit) override;
private:
	UPROPERTY()
	TSet<UUnit*> Units;
};
