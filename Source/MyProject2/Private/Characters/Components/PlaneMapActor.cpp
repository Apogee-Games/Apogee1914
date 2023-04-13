
#include "Characters/Components/PlaneMapActor.h"

FVector3d APlaneMapActor::GetNewPosition(FVector3d Position, FVector3d Direction, float DeltaTime)
{
	Direction.Normalize();
	return ClampVector(Position + Direction * SpeedVector * DeltaTime, MinPosition, MaxPosition);
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

FQuat APlaneMapActor::GetNewRotation(FVector3d Position, FVector3d NewPosition, FQuat Rotation)
{
	const FRotator DeltaRotation = FRotator(PitchDelta * (NewPosition.X - Position.X), 0, 0);
	const FQuat NewRotation = Rotation * DeltaRotation.Quaternion();
	FRotator Rotator = NewRotation.Rotator();
	Rotator.Pitch = FMath::Clamp(Rotator.Pitch, MinPitch, MaxPitch);
	return Rotator.Quaternion();	
}
