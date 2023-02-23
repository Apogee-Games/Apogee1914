#pragma once

class AHumanPlayerPawn;

class FPawnState
{
public:
	virtual ~FPawnState() = default;
	
	virtual TSharedPtr<FPawnState> LeftClick(AHumanPlayerPawn* Pawn) = 0;

	virtual TSharedPtr<FPawnState> RightClick(AHumanPlayerPawn* Pawn) = 0;
};
