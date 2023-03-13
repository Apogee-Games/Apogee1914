#pragma once
#include "Military/Instances/Units/Unit.h"

#include "UnitsSelectionComponent.generated.h"

class AHumanPlayerPawn;

UCLASS()
class UUnitsSelectionComponent: public USceneComponent
{
	GENERATED_BODY()
public:
	void SelectUnits(const TArray<UUnit*>& Units);

	void SelectUnit(UUnit* Unit);

	void ClearSelectedUnits();

	const TArray<UUnit*>& GetSelectedUnits() const;
private:
	UPROPERTY()
	TArray<UUnit*> SelectedUnits;

	void SelectedUnitsWereUpdated() const;
};
