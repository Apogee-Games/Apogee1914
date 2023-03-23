#pragma once
#include "Fraction.h"
#include "Administration/Descriptions/ParliamentDescription.h"

#include "Parliament.generated.h"

UCLASS()
class UParliament: public UObject
{
	GENERATED_BODY()
public:
	void Init(FParliamentDescription* Description);

	const FText& GetName() const;
	
	const TMap<FName, UFraction*>& GetFractionsMap() const;
private:
	FText ParliamentName;
	
	UPROPERTY()
	TMap<FName, UFraction*> Fractions;
};
