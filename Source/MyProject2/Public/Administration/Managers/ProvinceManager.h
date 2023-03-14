﻿#pragma once
#include "Engine/DataTable.h"
#include "Administration/Instances/Province.h"
#include "Administration/Interfaces/Observable/ProvinceControllingCountryObservable.h"
#include "ProvinceManager.generated.h"

class UUnit;

UCLASS()
class UProvinceManager : public UWorldSubsystem, public IProvinceControllingCountryObservable
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UProvince* GetProvince(const FColor& ProvinceColor) const;
	
	UProvince* GetProvince(const FName& ProvinceColorHex) const;

	const TArray<UProvince*>& GetAllProvinces() const;

	void UnitMovedIn(UProvince* Province, UUnit* Unit);

private:
	UPROPERTY()
	TMap<FName, UProvince*> ProvinceMap;

	UPROPERTY()
	TArray<UProvince*> ProvincesArray;

	void InitProvinces(UDataTable* ProvinceDescriptionDataTable, UDataTable* TerrainDescriptionDataTable, UDataTable* ResourcesDescriptionDataTable);
};