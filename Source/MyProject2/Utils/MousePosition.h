#pragma once
#include "GameFramework/PlayerController.h"

class FMousePosition
{
public:
	explicit FMousePosition(const APlayerController* PlayerController);

	FVector GetMouseLocation() const;

	FVector GetMouseDirection() const;
private:
	FVector MouseLocation;

	FVector MouseDirection;
};
