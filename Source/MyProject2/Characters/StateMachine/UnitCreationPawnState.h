#pragma once
#include "PawnState.h"

class FUnitCreationPawnState: public FPawnState
{
public:
	static TSharedPtr<FPawnState> GetInstance();

	virtual TSharedPtr<FPawnState> LeftClick(AHumanPlayerPawn* Pawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(AHumanPlayerPawn* Pawn) override;
	
private:
	FUnitCreationPawnState();
	
	inline static TSharedPtr<FUnitCreationPawnState> Instance;
};
