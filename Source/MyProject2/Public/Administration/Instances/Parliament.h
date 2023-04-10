#pragma once
#include "Fraction.h"
#include "Administration/Descriptions/ParliamentDescription.h"

#include "Parliament.generated.h"

UCLASS()
class UParliament: public UObject
{
	GENERATED_BODY()
public:
	void Init(const FParliamentDescription& Description);

	const FText& GetName() const;
	
	const TMap<UIdeologyDescription*, UFraction*>& GetFractionsMap() const;
private:
	FText Name;
	
	UPROPERTY()
	TMap<UIdeologyDescription*, UFraction*> Fractions;
};
