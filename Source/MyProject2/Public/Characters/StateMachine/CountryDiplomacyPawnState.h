#pragma once
#include "Characters/StateMachine/PawnState.h"


class FCountryDiplomacyPawnState : public FPawnState
{
public:
	static TSharedPtr<FPawnState> GetInstance();

	virtual TSharedPtr<FPawnState> LeftClick(APawn* ProvidedPawn) override;

	virtual TSharedPtr<FPawnState> RightClick(APawn* ProvidedPawn) override;

	virtual bool MustWidgetBeVisible(UUserWidget* Widget) override;

	virtual bool CanWidgetBeVisible(UUserWidget* Widget) override;
private:
	FCountryDiplomacyPawnState();

	inline static TSharedPtr<FCountryDiplomacyPawnState> Instance;
};
