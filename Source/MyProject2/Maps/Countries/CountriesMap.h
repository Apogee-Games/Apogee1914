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

	void UpdateCountriesMapColors(const TArray<UProvince*>& Provinces) const;

	void UpdateAllCountriesMapColors() const;
	
private:
	int CrossLineWidth = 10;
	
	UPROPERTY()	
	UTexture2D* CountriesMapTexture;

	FVector2D SizeVector;

	FRunnableThread* UpdateCountryColor(UProvince* Province, FColor* CountriesColor) const;
};
