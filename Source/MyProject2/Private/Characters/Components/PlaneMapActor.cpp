
#include "Characters/Components/PlaneMapActor.h"

FVector3d APlaneMapActor::GetNewPosition(FVector3d Position, FVector3d Direction, float Lenght)
{
	Direction.Normalize();
	return ClampVector(Position + Direction * Lenght, MinPosition, MaxPosition);
}

FVector2d APlaneMapActor::GetMapPosition(FVector3d WorldPosition)
{
	WorldPosition /= PlaneSideSize;
	return FVector2D(WorldPosition.Y, 1.0 - WorldPosition.Z);
}

FVector3d APlaneMapActor::GetWorldPosition(FVector2d MapPosition)
{
	return FVector3d(0, MapPosition.X, 1 - MapPosition.Y) * PlaneSideSize;
}

FQuat APlaneMapActor::GetNewRotation(FVector3d Position, FVector3d NewPosition)
{
	return FRotator(90 * (NewPosition.X - Position.X) / (MaxPosition.X - MinPosition.X), 0, 0).Quaternion();	
}
