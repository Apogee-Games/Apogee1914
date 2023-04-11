   #include "Characters/Components/SphereMapActor.h"

#include "VectorTypes.h"


  FVector3d ASphereMapActor::GetNewPosition(FVector3d Position, FVector3d Direction, float Lenght)
{ 	

  	/*Direction.Normalize(); 
  	float NewRadius =FVector3d::Dist( FVector3d(159, 95, 81), Position);
  	double AngleX = (Direction * Lenght).X / NewRadius;
    double AngleY = (Direction * Lenght).Y / NewRadius;
    double AngleZ = (Direction * Lenght).Z / NewRadius;
  	
  	FVector Vector = Position - FVector3d(159, 95, 81);
  	FRotator Rotator(AngleX, AngleY, AngleZ);
  	FVector RotatedVector = Rotator.RotateVector(Vector);
  	return RotatedVector + FVector3d(159, 95, 81); 	*/
  	 Direction.Normalize();
  	 return Position + Direction * Lenght;
  	
  
}

FVector2d ASphereMapActor::GetMapPosition(FVector3d WorldPosition)
{
  	/*float phi = atan2(WorldPosition.Y - 95, WorldPosition.X - 159) / (2 * PI) + 0.5;
  	float theta = acos((WorldPosition.Z - 81) / 160) / PI;
  	return FVector2d(phi, theta);
  	*/
  	
  	
  	//float Radius=sqrt((WorldPosition.X - 159)*(WorldPosition.X - 159)+(WorldPosition.Y - 95)*(WorldPosition.Y - 95)+(WorldPosition.Z - 81)*(WorldPosition.Z - 81));
  	FVector Vector= WorldPosition-SphereCenter;
  	if(Radius==-1) Radius=Vector.Size();
  	float theta = atan2( WorldPosition.X - 159,WorldPosition.Y - 95) / (2 * PI) + 0.5;
  	float phi = acos((WorldPosition.Z - 81) / Radius) / PI;
  
  	return FVector2d( theta,phi);
  
  	
  	
}


FVector3d ASphereMapActor::GetWorldPosition(FVector2d MapPosition)
{
  	/*float phi = MapPosition.X * PI * 2;
  	float theta = (MapPosition.Y - 0.5) * PI;
  	float x = 159 +  160* sin(theta) * cos(phi);
  	float y = 95 + 160 * sin(theta) * sin(phi);
  	float z = 81 + 160 * cos(theta);
  	return FVector3d(x, y, z);*/
  	
  	
  	float theta = (MapPosition.X-0.5) * PI * 2;
  	float phi = (MapPosition.Y ) * PI;
  	float x = 95 +  Radius* sin(phi) * sin(theta);
  	float y = 159 + Radius * cos(theta) * sin(phi);
  	float z = 81 + Radius * cos(phi);
  	
  	return FVector3d(x, y, z);
  	
  	
}

FQuat ASphereMapActor::GetNewRotation(FVector3d Position, FVector3d NewPosition)
{
	 // FVector ForwardVector = (NewPosition - Position).GetSafeNormal();
	 // FVector RightVector = FVector::CrossProduct(ForwardVector, FVector::UpVector).GetSafeNormal();
	 // FVector UpVector = FVector::CrossProduct(RightVector, ForwardVector).GetSafeNormal();
	 // FMatrix RotationMatrix(ForwardVector, RightVector, UpVector, FVector::ZeroVector);
	 // return FQuat(RotationMatrix);
  	
  // return (FVector3d(159, 95, 81) - NewPosition).Rotation().Quaternion();
  	////////////////////////////////////////////
  	// Translate the positions to be relative to the sphere's center
  	
  	Position -= SphereCenter;
  	NewPosition -= SphereCenter;

  	// Find the axis of rotation and the angle of rotation between the two vectors
  	FVector3d RotationAxis = FVector3d::CrossProduct(Position, NewPosition).GetSafeNormal();
  	float RotationAngle = FMath::Acos(FVector3d::DotProduct(Position.GetSafeNormal(), NewPosition.GetSafeNormal()));

  	// Construct a quaternion representing the rotation
  	return FQuat(RotationAxis, RotationAngle);
  	//////////////////////////////////////////////////////

  	
  	
  	
  	
}


