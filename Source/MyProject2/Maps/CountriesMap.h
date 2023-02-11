#pragma once
#include "MyProject2/MyGameState.h"
#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "CountriesMap.generated.h"

UCLASS()
class UCountriesMap: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void UpdateCountriesMapColors() const;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
private:
	int CrossLineWidth = 10;
	
	UPROPERTY()	
	UTexture2D* CountriesMapTexture;

	UPROPERTY()	
	UTexture2D* ProvincesMapTexture;

	FVector2D SizeVector;

	TArray<int> FindProvincesBorders(const FColor* ProvincesColor, const int Width, const int Height, UCountriesManager* CountriesManager) const;

	int* FindDistancesFromBorders(const TArray<int>& Borders, const int Width, const int Height) const;

	const FColor* GetColor(const FVector2D& Position, const FColor& ProvinceColor, UCountriesManager* CountriesManager) const;
};
