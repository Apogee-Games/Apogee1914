#pragma once
#include "Military/Instances/Units/Unit.h"

#include "UnitsListCarrier.generated.h"

UCLASS()
class UUnitsListCarrier: public UObject
{
	GENERATED_BODY()
public:
	void AddUnit(UUnit* Unit);

	void RemoveUnit(UUnit* Unit);
	
	bool IsEmpty() const;

	int32 Num() const;

	UUnit* GetFirst() const;

	const TArray<UUnit*>& GetUnits() const;
	
private:
	UPROPERTY()
	TArray<UUnit*> Units;
};
