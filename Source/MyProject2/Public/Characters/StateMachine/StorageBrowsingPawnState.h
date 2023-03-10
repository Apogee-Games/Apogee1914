#pragma once
#include "PawnState.h"

class FStorageBrowsingPawnState: public FPawnState
{
public:
	static TSharedPtr<FPawnState> GetInstance();

	virtual TSharedPtr<FPawnState> LeftClick(AHumanPlayerPawn* Pawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(AHumanPlayerPawn* Pawn) override;

	virtual bool MustWidgetBeVisible(UUserWidget* Widget) override;

	virtual bool CanWidgetBeVisible(UUserWidget* Widget) override;

private:
	FStorageBrowsingPawnState();
	
	inline static TSharedPtr<FStorageBrowsingPawnState> Instance;
};
