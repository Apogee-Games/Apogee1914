#pragma once
#include "Administration/Descriptions/ParliamentDescription.h"

#include "Parliament.generated.h"

UCLASS()
class UParliament: public UObject
{
	GENERATED_BODY()
public:
	void Init(FParliamentDescription* Description);

	const TMap<FName, FFractionDescription>& GetFractionsMap() const;
private:
	TMap<FName, FFractionDescription> FractionsMap;
};
