
#include "Maps/Objects/ObjectMap.h"

#include "Administration/Managers/ProvinceManager.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Utils/TextureUtils.h"

void UObjectMap::CalculateProvincesCenters()
{
	for (const auto& Province : GetWorld()->GetSubsystem<UProvinceManager>()->GetAllProvinces())
	{
		CalculateProvinceCenter(Province->GetId());
	}
}

void UObjectMap::CalculateProvinceCenter(const FColor& Color)
{
	ProvinceCenters.Add(Color, {0, 0});
	
	const UProvincesMap* ProvincesMap = GetWorld()->GetSubsystem<UProvincesMap>();
	
	const TArray<int32>& Positions = ProvincesMap->GetProvincePositions(Color);
	const FVector2d SizeVector = ProvincesMap->GetSizeVector();

	for (const auto& Position : Positions)
	{
		ProvinceCenters[Color] += FTextureUtils::GetPositionVector(Position, SizeVector);
	}

	ProvinceCenters[Color] = ProvinceCenters[Color] / Positions.Num() / SizeVector;
}

FVector2d UObjectMap::GetProvinceCenter(const FColor& Color)
{
	return ProvinceCenters[Color];
}

void UObjectMap::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GetWorld()->GetSubsystem<UProvincesMap>()->RegisterOnFullInitializationAction(this, &UObjectMap::CalculateProvincesCenters);
}
