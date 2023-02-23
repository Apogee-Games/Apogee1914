#pragma once
#include "PawnState.h"

class FNoActionPawnState: public FPawnState
{
public:

	static TSharedPtr<FPawnState> GetInstance();
	
	virtual TSharedPtr<FPawnState> LeftClick(AHumanPlayerPawn* Pawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(AHumanPlayerPawn* Pawn) override;
	
	virtual ~FNoActionPawnState() override;

private:
	FNoActionPawnState();
	
	inline static TSharedPtr<FNoActionPawnState> Instance;
};
