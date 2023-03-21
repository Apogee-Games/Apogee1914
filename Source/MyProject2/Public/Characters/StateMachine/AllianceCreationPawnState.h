#pragma once
#include "PawnState.h"

class FAllianceCreationPawnState: public FPawnState
{
public:
	static TSharedPtr<FPawnState> GetInstance();

	virtual TSharedPtr<FPawnState> LeftClick(APawn* ProvidedPawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(APawn* ProvidedPawn) override;
	
	virtual bool MustWidgetBeVisible(UUserWidget* Widget) override;
	
	virtual bool CanWidgetBeVisible(UUserWidget* Widget) override;
	
private:
	FAllianceCreationPawnState();
	
	inline static TSharedPtr<FAllianceCreationPawnState> Instance;
};
