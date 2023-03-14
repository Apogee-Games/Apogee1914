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

	virtual TSharedPtr<FPawnState> LeftClick(AHumanPlayerPawn* Pawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(AHumanPlayerPawn* Pawn) override;

	virtual bool MustWidgetBeVisible(UUserWidget* Widget) override;
	
	virtual bool CanWidgetBeVisible(UUserWidget* Widget) override;
	
private:
	FMilitaryControlPawnState();
	
	inline static TSharedPtr<FMilitaryControlPawnState> Instance;
};
