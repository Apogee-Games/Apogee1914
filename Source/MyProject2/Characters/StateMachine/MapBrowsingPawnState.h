#pragma once
#include "PawnState.h"

class FMapBrowsingPawnState: public FPawnState
{
public:

	static TSharedPtr<FPawnState> GetInstance();
	
	virtual TSharedPtr<FPawnState> LeftClick(AHumanPlayerPawn* Pawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(AHumanPlayerPawn* Pawn) override;

	virtual bool MustWidgetBeVisible(UUserWidget* Widget) override;
	
	virtual bool CanWidgetBeVisible(UUserWidget* Widget) override;
private:
	FMapBrowsingPawnState();
	
	inline static TSharedPtr<FMapBrowsingPawnState> Instance;
};
