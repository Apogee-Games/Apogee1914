#pragma once
#include "MyProject2/Province/Descriptions/ProvinceDescription.h"
#include "MyProject2/World/Country.h"
#include "MyProject2/World/State.h"
#include "Engine/DataTable.h"
#include "ProvinceManager.generated.h"

UCLASS()
class UProvinceManager : public UObject
{
	GENERATED_BODY()
	
public:
	UProvinceManager();

	FProvinceDescription* GetProvince(const FColor& ProvinceColor) const;	
	
	FColor GetCountryColor(const FColor& ProvinceColor) const;

	FState* GetState(const FString& StateId) const;

	bool AreProvincesInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const;
	
	bool AreProvincesNotInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const;
	
	UTexture2D* GetProvincesMapTexture() const;

	UTexture2D* GetSelectionMapTexture() const;

	UTexture2D* GetCountriesMapTexture() const;

	UTexture2D* GetOutlinesMapTexture() const;

	
	
private:
	UPROPERTY()
	UDataTable* CountryDescriptionDataTable;
	
	UPROPERTY()
	UDataTable* StateDescriptionDataTable;
	
	UPROPERTY()
	UDataTable* ProvinceDescriptionDataTable;
	
	UPROPERTY()
	UTexture2D* ProvincesMapTexture;

	UPROPERTY()
	UTexture2D* SelectionMapTexture;

	UPROPERTY()
	UTexture2D* CountriesMapTexture;

	UPROPERTY()
	UTexture2D* OutlinesMapTexture;
};
