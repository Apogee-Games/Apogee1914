  #include "Characters/Components/SphereMapActor.h"

#include "VectorTypes.h"


  FVector3d ASphereMapActor::GetNewPosition(FVector3d Position, FVector3d Direction, float Lenght)
{ 	

  	Direction.Normalize(); 
  	float NewRadius =FVector3d::Dist( FVector3d(159, 95, 81), Position);
  	double AngleX = (Direction * Lenght).X / NewRadius;
    double AngleY = (Direction * Lenght).Y / NewRadius;
    double AngleZ = (Direction * Lenght).Z / NewRadius;
  	
  	FVector Vector = Position - FVector3d(159, 95, 81);
  	FRotator Rotator(AngleX, AngleY, AngleZ);
  	FVector RotatedVector = Rotator.RotateVector(Vector);
  	return RotatedVector + FVector3d(159, 95, 81);
  	
  	
  
}

FVector2d ASphereMapActor::GetMapPosition(FVector3d WorldPosition)
{
  	FVector3d NormalizedPosition = WorldPosition.GetSafeNormal();
  	float Latitude = FMath::Asin(NormalizedPosition.Z) / PI + 0.5f;
  	float Longitude = FMath::Atan2(NormalizedPosition.Y, NormalizedPosition.X) / (2 * PI) + 0.5f;
  	return FVector2d(Longitude, 1.0 - Latitude);
}


FVector3d ASphereMapActor::GetWorldPosition(FVector2d MapPosition)
{
  	float Latitude = (1.0 - MapPosition.Y) * PI - PI / 2.0f;
  	float Longitude = (MapPosition.X - 0.5f) * 2 * PI;
  	FVector3d NormalizedPosition = FVector3d(
		  FMath::Cos(Latitude) * FMath::Cos(Longitude),
		  FMath::Cos(Latitude) * FMath::Sin(Longitude),
		  FMath::Sin(Latitude));
  	return NormalizedPosition * 165;
}

FQuat ASphereMapActor::GetNewRotation(FVector3d Position, FVector3d NewPosition)
{
	 // FVector ForwardVector = (NewPosition - Position).GetSafeNormal();
	 // FVector RightVector = FVector::CrossProduct(ForwardVector, FVector::UpVector).GetSafeNormal();
	 // FVector UpVector = FVector::CrossProduct(RightVector, ForwardVector).GetSafeNormal();
	 // FMatrix RotationMatrix(ForwardVector, RightVector, UpVector, FVector::ZeroVector);
	 // return FQuat(RotationMatrix);
  	
  //return (FVector3d(159, 95, 81) - NewPosition).Rotation().Quaternion();
  	////////////////////////////////////////////
  	// Translate the positions to be relative to the sphere's center
  	/*FVector3d SphereCenter(159, 95, 81);
  	Position -= SphereCenter;
  	NewPosition -= SphereCenter;

  	// Find the axis of rotation and the angle of rotation between the two vectors
  	FVector3d RotationAxis = FVector3d::CrossProduct(Position, NewPosition).GetSafeNormal();
  	float RotationAngle = FMath::Acos(FVector3d::DotProduct(Position.GetSafeNormal(), NewPosition.GetSafeNormal()));

  	// Construct a quaternion representing the rotation
  	return FQuat(RotationAxis, RotationAngle);*/
  	//////////////////////////////////////////////////////
  	// Translate the positions to be relative to the sphere's center
  	FVector3d SphereCenter(159, 95, 81);
  	Position -= SphereCenter;
  	NewPosition -= SphereCenter;

  	// Apply the sphere's rotation
  	FRotator SphereRotation(20, 0, 85);
  	Position = SphereRotation.RotateVector(Position);
  	NewPosition = SphereRotation.RotateVector(NewPosition);

  	// Find the axis of rotation and the angle of rotation between the two vectors
  	FVector3d RotationAxis = FVector3d::CrossProduct(Position, NewPosition).GetSafeNormal();
  	float RotationAngle = FMath::Acos(FVector3d::DotProduct(Position.GetSafeNormal(), NewPosition.GetSafeNormal()));

  	// Construct a quaternion representing the rotation
  	FQuat RotationQuat = FQuat(RotationAxis, RotationAngle);

  	// Apply the inverse of the sphere's rotation
  	RotationQuat = SphereRotation.GetInverse().Quaternion() * RotationQuat * SphereRotation.Quaternion();

  	return RotationQuat;
  	
  	
}


