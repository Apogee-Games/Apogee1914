#pragma once

class AHumanPlayerPawn;

class FPawnState
{
public:
	// TODO: use c++ singleton implementation
	
	virtual ~FPawnState() = default;
	
	virtual TSharedPtr<FPawnState> LeftClick(AHumanPlayerPawn* Pawn) = 0;

	virtual TSharedPtr<FPawnState> RightClick(AHumanPlayerPawn* Pawn) = 0;

	virtual bool MustWidgetBeVisible(UUserWidget* Widget) = 0;

	virtual bool CanWidgetBeVisible(UUserWidget* Widget) = 0;
};
