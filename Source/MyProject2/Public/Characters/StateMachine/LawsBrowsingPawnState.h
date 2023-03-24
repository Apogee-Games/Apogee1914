#pragma once
#include "PawnState.h"

class FLawsBrowsingPawnState: public FPawnState 
{
public:
	static TSharedPtr<FPawnState> GetInstance();
	
	virtual TSharedPtr<FPawnState> LeftClick(APawn* ProvidedPawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(APawn* ProvidedPawn) override;

	virtual bool MustWidgetBeVisible(UUserWidget* Widget) override;
	
	virtual bool CanWidgetBeVisible(UUserWidget* Widget) override;
private:
	FLawsBrowsingPawnState();
	
	inline static TSharedPtr<FLawsBrowsingPawnState> Instance;
};
