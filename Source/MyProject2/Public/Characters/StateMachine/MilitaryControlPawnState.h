#pragma once
#include "PawnState.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"

class UProvince;
class UUnitsMover;
class UUnit;

class FMilitaryControlPawnState: public FPawnState
{
public:
	static TSharedPtr<FPawnState> GetInstance();

	virtual TSharedPtr<FPawnState> LeftClick(APawn* ProvidedPawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(APawn* ProvidedPawn) override;

	virtual bool MustWidgetBeVisible(UUserWidget* Widget) override;
	
	virtual bool CanWidgetBeVisible(UUserWidget* Widget) override;
	
private:
	FMilitaryControlPawnState();
	
	inline static TSharedPtr<FMilitaryControlPawnState> Instance;
};
