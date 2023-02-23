#pragma once
#include "PawnState.h"

class FMilitaryControlPawnState: public FPawnState
{
public:
	static TSharedPtr<FPawnState> GetInstance();

	virtual TSharedPtr<FPawnState> LeftClick(AHumanPlayerPawn* Pawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(AHumanPlayerPawn* Pawn) override;
	
private:
	FMilitaryControlPawnState();
	
	inline static TSharedPtr<FMilitaryControlPawnState> Instance;
};
