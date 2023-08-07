#pragma once
#include "UnitsCollection.h"
#include "Military/Instances/Units/Collection.h"
#include "Military/Interfaces/Commandable.h"
#include "UnitsCollectionGroup.generated.h"

UCLASS()
class UUnitsCollectionGroup: public UObject, public TFMilitaryCollection<UUnitsCollection*>, public ICommandable
{
	GENERATED_BODY()
public:
	virtual void Init(UMilitaryBranchDescription* ProvidedMilitaryBranch) override;
	void Dissolve();
	
	virtual bool Add(UUnitsCollection* Collection) override;
	
	virtual bool Remove(UUnitsCollection* Collection) override;

	virtual const TSet<UUnitsCollection*>& GetAll() const override;

	virtual int32 GetSize() const override;

	virtual bool Contains(UUnitsCollection* Item) override;
	
	void ClearCollections();
private:
	UPROPERTY()
	TSet<UUnitsCollection*> Collections;
};
