#pragma once
#include "MyProject2/Administration/Interfaces/Observer/ProvinceOwningCountryObserver.h"
#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Interfaces/FOnFullInitialization.h"

#include "ProvincesMap.generated.h"

UCLASS()
class UProvincesMap: public UWorldSubsystem, public FOnFullInitialization, public IProvinceOwningCountryObserver
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	FVector2d GetSizeVector() const;

	const TArray<FColor>& GetColors() const;

	const TMap<FColor, TSet<FColor>>& GetNeighbours() const;

	//TODO: Think if it necessary to return it as reference 
	const FColor& GetColor(int32 Position) const;

	bool HasProvincePosition(const FColor& Color) const;
	
	const TArray<int32>& GetProvincePositions(const FColor& Color) const;

	virtual void ProvinceHasNewOwningCountry(UProvince* Province) override;
	
	virtual void Deinitialize() override;

private:
	UTexture2D* ProvincesMapTexture;
	
	TMap<FColor, TArray<int32>> ColorPosition;

	TMap<FColor, TSet<FColor>> Neighbours;

	TMap<TPair<FColor, FColor>, TArray<int32>> Borders;

	TArray<FColor> PositionColor;
	
	FVector2d SizeVector;
	
	void CalculateMappers(UTexture2D* ProvinceMap);

	void FindNeighbours();

	void CalculateBorders();

	void AddBorder(const FColor& A, const FColor& B, int i);
};