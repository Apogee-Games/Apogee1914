#include "Characters/Components/SphereMapActor.h"

#include "VectorTypes.h"


FVector3d ASphereMapActor::GetNewPosition(FVector3d Position, FVector3d Direction, FRotator Roation, float DeltaTime)
{
	Direction.Normalize();
	return Position + Roation.RotateVector(Direction) * SpeedVector * DeltaTime;
}

FVector2d ASphereMapActor::GetMapPosition(FVector3d WorldPosition)
{
	const FVector Vector = SphereRotation.UnrotateVector(WorldPosition - SphereCenter);
	const float theta = atan2(Vector.X, Vector.Y) / (2 * PI) + 0.5;
	const float phi = acos(Vector.Z / Radius) / PI;
	return FVector2d(theta, phi);
}

FVector3d ASphereMapActor::GetWorldPosition(FVector2d MapPosition)
{
	const float theta = (MapPosition.X - 0.5) * PI * 2;
	const float phi = (MapPosition.Y) * PI;
	const FVector DirectionVector(sin(phi) * sin(theta), cos(theta) * sin(phi), cos(phi));
	return SphereCenter + SphereRotation.RotateVector(DirectionVector) * Radius;
}

FQuat ASphereMapActor::GetNewRotation(FVector3d Position, FVector3d NewPosition, FQuat Rotation)
{
	return (SphereCenter - NewPosition).Rotation().Quaternion();
}