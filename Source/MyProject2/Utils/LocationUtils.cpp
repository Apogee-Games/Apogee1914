#include "LocationUtils.h"

#include "MousePosition.h"

FVector FLocationUtils::GetNormalizedPositionOnPlane(const AHumanPlayerPawn* Pawn)
{
	const FMousePosition MousePosition(Pawn->GetController<APlayerController>());
	FVector Point = FMath::RayPlaneIntersection(MousePosition.GetMouseLocation(),
												MousePosition.GetMouseDirection(),
												Plane);

	Point /= PlaneSize;

	Point.Z = 1 - Point.Z;

	return Point;
}
