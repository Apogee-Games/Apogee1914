#pragma once
#include "Administration/Descriptions/CountryDescription.h"
#include "Economics/Instances/Market.h"
#include "Economics/Instances/Strata.h"

#include "Country.generated.h"

UCLASS()
class UCountry: public UObject
{
	GENERATED_BODY()
	
public:
	void Init(FCountryDescription* CountryDescription);

	const FColor& GetColor() const;

	const FName& GetName() const;

	const FName& GetTag() const;

	UTexture2D* GetFlag() const;

	UStorage* GetStorage() const;

	TArray<UStorage*> GetStorages() const;
	
private:
	FName Name;

	FName Tag;

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

	UPROPERTY()
	UStorage* Storage;

	void InitStrata();

};