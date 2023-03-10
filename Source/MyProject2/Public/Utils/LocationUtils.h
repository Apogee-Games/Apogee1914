#pragma once
#include "Characters/HumanPlayerPawn.h"

class FLocationUtils
{
public:
	static FVector GetNormalizedPositionOnPlane(const AHumanPlayerPawn* Pawn);

	inline static const FVector PlaneNormal = FVector(1, 0, 0);

	inline static const FVector PlaneBase = FVector(0, 0, 0);

	inline static constexpr double PlaneSize = 200;

	inline static const UE::Math::TPlane<double> Plane = UE::Math::TPlane(PlaneBase, PlaneNormal);
};
