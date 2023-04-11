#include "Characters/Components/SphereMapActor.h"

#include "VectorTypes.h"


FVector3d ASphereMapActor::GetNewPosition(FVector3d Position, FVector3d Direction, float Lenght)
{
	Direction.Normalize();
	return Position + Direction * Lenght;
}

FVector2d ASphereMapActor::GetMapPosition(FVector3d WorldPosition)
{
	FVector Vector = WorldPosition - SphereCenter;
	if (Radius == -1) Radius = Vector.Size();
	float theta = atan2(WorldPosition.X - 159, WorldPosition.Y - 95) / (2 * PI) + 0.5;
	float phi = acos((WorldPosition.Z - 81) / Radius) / PI;
	return FVector2d(theta, phi);
}


FVector3d ASphereMapActor::GetWorldPosition(FVector2d MapPosition)
{
	float theta = (MapPosition.X - 0.5) * PI * 2;
	float phi = (MapPosition.Y) * PI;
	float x = 95 + Radius * sin(phi) * sin(theta);
	float y = 159 + Radius * cos(theta) * sin(phi);
	float z = 81 + Radius * cos(phi);
	return FVector3d(x, y, z);
}

FQuat ASphereMapActor::GetNewRotation(FVector3d Position, FVector3d NewPosition)
{
	Position -= SphereCenter;
	NewPosition -= SphereCenter;
	FVector3d RotationAxis = FVector3d::CrossProduct(Position, NewPosition).GetSafeNormal();
	float RotationAngle = FMath::Acos(FVector3d::DotProduct(Position.GetSafeNormal(), NewPosition.GetSafeNormal()));
	return FQuat(RotationAxis, RotationAngle);
}
