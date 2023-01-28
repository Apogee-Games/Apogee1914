#pragma once
#include "MyProject2/World/Country.h"
#include "MyProject2/World/State.h"
#include "Engine/DataTable.h"
#include "MyProject2/Province/Province.h"
#include "ProvinceManager.generated.h"

UCLASS()
class UProvinceManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UProvince* GetProvince(const FColor& ProvinceColor) const;
	
	UProvince* GetProvince(const FString& ProvinceColorHex) const;

	FColor GetCountryColor(const FColor& ProvinceColor) const;

	FState* GetState(const FString& StateId) const;

	bool AreProvincesInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const;
	
	bool AreProvincesNotInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const;
	
	void InitProvinces();

	TArray<FString>* GetCountriesTagsList();

	bool ExistsCountryWithSuchProvince(const FColor& ProvinceColor) const;

private:

	TArray<FString> CountriesTagsList;

	UPROPERTY()
	TMap<FName, UProvince*> ProvinceMap;
	
	UPROPERTY()
	UDataTable* CountryDescriptionDataTable;
	
	UPROPERTY()
	UDataTable* StateDescriptionDataTable;
	
	UPROPERTY()
	UDataTable* ProvinceDescriptionDataTable;
	
	UPROPERTY()
	UDataTable* TerrainDescriptionDataTable;

};
