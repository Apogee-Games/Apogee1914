#pragma once
#include "Scenario.h"
#include "Administration/Instances/Province.h"
#include "SelectionMap.generated.h"

UCLASS(Abstract, Blueprintable)
class USelectionMap : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	UProvince* SelectProvince(const FVector2d& Point);
	
	UProvince* GetProvince(const FVector2d& Point) const;
	
	FColor GetProvinceColor(const FVector2d& Point) const;

	UPROPERTY(EditDefaultsOnly)
	FColor SelectedProvinceColor = FColor(75, 75, 150);

	UPROPERTY(EditDefaultsOnly)
	FColor NonSelectedProvinceColor = FColor(0, 0, 0);
private:
	UPROPERTY()
	UTexture2D* SelectionMapTexture;

	FVector2D SizeVector;
	
	FColor SelectedProvince = FColor(0, 0, 0);

	void SelectProvince(const FColor& Color);

	void Clear();

	void Init(UScenario* Scenario);
};
