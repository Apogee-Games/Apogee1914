#pragma once
#include "MapActor.h"
#include "SphereMapActor.generated.h"

UCLASS()
class  ASphereMapActor : public AMapActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FRotator SphereRotator = FRotator(20, 0, 85);
	  UPROPERTY(EditDefaultsOnly)
	 FVector3d MinPosition = FVector3d(-100, 0, 0);
	
	  UPROPERTY(EditDefaultsOnly)
	  FVector3d MaxPosition = FVector3d(-15, 200, 200);
	
	
	// double SphereSize = 200*PI;
	double PlaneSize = 200;
	float Radius;
	 FVector3d SphereCenter=FVector3d (159, 95, 81);

	//ASphereMapActor();
	
	virtual FVector3d GetNewPosition(FVector3d Position, FVector3d Direction, float Lenght) override;
	
	virtual FVector2d GetMapPosition(FVector3d WorldPosition) override;

	virtual FVector3d GetWorldPosition(FVector2d MapPosition) override;

	virtual FQuat GetNewRotation(FVector3d Position, FVector3d NewPosition) override;
};
