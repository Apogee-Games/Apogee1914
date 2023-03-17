#pragma once
#include "PawnState.h"

class FCountrySelectionPawnState: public FPawnState
{
public:
	static TSharedPtr<FPawnState> GetInstance();

	virtual TSharedPtr<FPawnState> LeftClick(APawn* ProvidedPawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(APawn* ProvidedPawn) override;

	virtual bool MustWidgetBeVisible(UUserWidget* Widget) override;
	
	virtual bool CanWidgetBeVisible(UUserWidget* Widget) override;
	
private:
	FCountrySelectionPawnState();
	
	inline static TSharedPtr<FCountrySelectionPawnState> Instance;
};
