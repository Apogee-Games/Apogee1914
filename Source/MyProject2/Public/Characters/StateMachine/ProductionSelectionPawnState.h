#pragma once
#include "PawnState.h"

class FProductionSelectionPawnState: public FPawnState
{
public:
	static TSharedPtr<FPawnState> GetInstance();

	virtual TSharedPtr<FPawnState> LeftClick(APawn* ProvidedPawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(APawn* ProvidedPawn) override;

	virtual bool MustWidgetBeVisible(UUserWidget* Widget) override;

	virtual bool CanWidgetBeVisible(UUserWidget* Widget) override;

private:
	FProductionSelectionPawnState();
	
	inline static TSharedPtr<FProductionSelectionPawnState> Instance;
};
