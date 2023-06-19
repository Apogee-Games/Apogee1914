#pragma once
#include "Scenario.h"
#include "Administration/Interfaces/Observer/ProvinceOwningCountryObserver.h"
#include "Interfaces/BaseManager.h"
#include "Interfaces/FOnFullInitialization.h"

#include "ProvincesMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UProvincesMap: public UBaseManager, public IProvinceOwningCountryObserver
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	FVector2d GetSizeVector() const;

	const TArray<FColor>& GetColors() const;

	const TMap<FColor, TSet<FColor>>& GetNeighbourColors() const;

	const TMap<UProvince*, TSet<UProvince*>>& GetNeighbourProvinces();

	const FColor& GetColor(int32 Position) const;

	bool HasProvincePosition(const FColor& Color) const;
	
	const TArray<int32>& GetProvincePositions(const FColor& Color) const;

	virtual void ProvinceHasNewOwningCountry(UProvince* Province) override;

	virtual ELoadStage GetLoadStage() override;
private:
	UPROPERTY()
	UTexture2D* ProvincesMapTexture;

	TMap<UProvince*, TSet<UProvince*>> NeighbourProvinces;
	
	TMap<FColor, TArray<int32>> ColorPosition;

	TMap<FColor, TSet<FColor>> NeighbourColors;

	TMap<TPair<FColor, FColor>, TArray<int32>> Borders;

	TArray<FColor> PositionColor;
	
	FVector2d SizeVector;
	
	void CalculateMappers(UTexture2D* ProvinceMap);

	void FindNeighbours();

	void CalculateBorders();

	void AddBorder(const FColor& A, const FColor& B, int32 i);

	void Clear();
	
	void Init(UScenario* Scenario);
};
