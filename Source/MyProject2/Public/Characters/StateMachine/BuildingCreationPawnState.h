#pragma once
#include "PawnState.h"

class FBuildingCreationPawnState : public FPawnState
{
public:
	static TSharedPtr<FPawnState> GetInstance();

	virtual TSharedPtr<FPawnState> LeftClick(APawn* ProvidedPawn) override;
	
	virtual TSharedPtr<FPawnState> RightClick(APawn* ProvidedPawn) override;
	
	virtual bool MustWidgetBeVisible(UUserWidget* Widget) override;
	
	virtual bool CanWidgetBeVisible(UUserWidget* Widget) override;
	
private:
	FBuildingCreationPawnState();
	
	inline static TSharedPtr<FBuildingCreationPawnState> Instance;
};
