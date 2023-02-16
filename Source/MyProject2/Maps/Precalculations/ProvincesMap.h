#pragma once
#include "MyProject2/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Maps/Flags/ProvincesBox.h"

#include "ProvincesMap.generated.h"

UCLASS()
class UProvincesMap: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	FVector2d GetSizeVector() const;

	//TODO: Think if it necessary to return it as refecence 
	const FColor& GetColor(int32 Position) const;

	const TArray<int32>& GetProvincePositions(const FColor& Color) const;

	int GetProvincesDistance(int Position) const;

	int GetStatesDistance(int Position) const;

	int GetCountriesDistance(int Position) const;

	const int* GetProvincesDistances() const;

	const int* GetStatesDistances() const;

	const int* GetCountriesDistances() const;
	
	virtual void Deinitialize() override;
private:
	UTexture2D* ProvincesMapTexture;
	
	TMap<FColor, TArray<int32>> ColorPosition;

	TMap<FColor, TSet<FColor>> Neighbours;

	TMap<TPair<FColor, FColor>, TArray<int32>> Borders;

	TArray<FProvincesBox> Boxes;

	TMap<UProvince*, FProvincesBox> ProvinceBox;

	FColor* PositionColor;
	
	FVector2d SizeVector;
	
	int32* ProvincesDistances;

	int32* StatesDistances;

	int32* CountriesDistances;

	void CalculateMappers(UTexture2D* ProvinceMap);

	void FindNeighbours();
	
	void CalculateBoxes();

	void AddProvincesToBox(FProvincesBox& Box, UProvince* FromProvince, UCountry* Country, UProvinceManager* ProvinceManager);
	
	void CalculateDistances() const;

	FRunnableThread* CalculateProvincesDistances() const;
	
	FRunnableThread* CalculateStatesDistances() const;

	FRunnableThread* CalculateCountriesDistances() const;
};
