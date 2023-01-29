#pragma once
#include "MyProject2/MyGameState.h"
#include "MyProject2/Administration/Managers/ProvinceManager.h"
#include "CountriesMap.generated.h"

UCLASS()
class UCountriesMap: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void UpdateCountriesMapColors() const;

private:
	UPROPERTY()	
	UTexture2D* CountriesMapTexture;

	UPROPERTY()	
	UTexture2D* ProvincesMapTexture;

	FVector2D SizeVector;

	TArray<int> FindProvincesBorders(const FColor* ProvincesColor, const int Width, const int Height, UProvinceManager* GameState) const;

	int* FindDistancesFromBorders(const TArray<int>& Borders, const int Width, const int Height) const;
};
