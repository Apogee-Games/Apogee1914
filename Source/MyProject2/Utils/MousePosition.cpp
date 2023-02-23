#include "MousePosition.h"

FMousePosition::FMousePosition(const APlayerController* PlayerController)
{
	PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
}

FVector FMousePosition::GetMouseLocation() const
{
	return MouseLocation;
}

FVector FMousePosition::GetMouseDirection() const
{
	return MouseDirection;
}
