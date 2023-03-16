#pragma once
#include "Administration/Interfaces/Observer/ProvinceOwningCountryObserver.h"
#include "Interfaces/FOnFullInitialization.h"

#include "ProvincesMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UProvincesMap: public UWorldSubsystem, public FOnFullInitialization, public IProvinceOwningCountryObserver
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	FVector2d GetSizeVector() const;

	const TArray<FColor>& GetColors() const;

	const TMap<FColor, TSet<FColor>>& GetNeighbours() const;

	const FColor& GetColor(int32 Position) const;

	bool HasProvincePosition(const FColor& Color) const;
	
	const TArray<int32>& GetProvincePositions(const FColor& Color) const;

	virtual void ProvinceHasNewOwningCountry(UProvince* Province) override;
private:
	UPROPERTY()
	UTexture2D* ProvincesMapTexture;
	
	TMap<FColor, TArray<int32>> ColorPosition;

	TMap<FColor, TSet<FColor>> Neighbours;

	TMap<TPair<FColor, FColor>, TArray<int32>> Borders;

	TArray<FColor> PositionColor;
	
	FVector2d SizeVector;
	
	void CalculateMappers(UTexture2D* ProvinceMap);

	void FindNeighbours();

	void CalculateBorders();

	void AddBorder(const FColor& A, const FColor& B, int32 i);
};