#pragma once
#include "CountryIdeologyParameters.h"
#include "Administration/Descriptions/IdeologyDescription.h"
#include "Administration/Descriptions/ParliamentDescription.h"
#include "Engine/DataTable.h"
#include "CountryDescription.generated.h"

UCLASS()
class UCountryDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()	
public:
	UPROPERTY(EditDefaultsOnly)
	FName Tag;

	UPROPERTY(EditDefaultsOnly)
	UIdeologyDescription* CurrentIdeology;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FCountryIdeologyParameters> Ideologies;

	UPROPERTY(EditDefaultsOnly)
	bool HasFirstChamber = false;

	UPROPERTY(EditDefaultsOnly)
	bool HasTwoChambers = false;
	
	UPROPERTY(EditDefaultsOnly)
	FParliamentDescription FirstChamber;
	
	UPROPERTY(EditDefaultsOnly)
	FParliamentDescription SecondChamber;
};
