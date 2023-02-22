#pragma once
#include "MyProject2/Administration/Descriptions/CountryDescription.h"
#include "MyProject2/Economics/Instances/Public/Market.h"
#include "MyProject2/Economics/Instances/Public/Strata.h"

#include "Country.generated.h"

UCLASS()
class UCountry: public UObject
{
	GENERATED_BODY()
	
public:
	void Init(FCountryDescription* CountryDescription);

	const FColor& GetColor() const;

	const FString& GetName() const;

	const FString& GetTag() const;

	UTexture2D* GetFlag() const;
	
private:
	FString Name;

	FString Tag;

	FColor Color;

	UPROPERTY()
	UTexture2D* Flag = nullptr;

	UPROPERTY()
	UMarket* Market;
	
	UPROPERTY()
	UStrata* LowerStrata;
	
	UPROPERTY()
	UStrata* MiddleStrata;
	
	UPROPERTY()
	UStrata* UpperStrata;

};
