
#include "Maps/Objects/ObjectMap.h"

#include "Administration/Managers/ProvinceManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Utils/TextureUtils.h"

void UObjectMap::CalculateProvinceCenter(const FColor& Color)
{
	ProvinceCenters.Add(Color, {0, 0});
	
	const UProvincesMap* ProvincesMap = GetGameInstance()->GetSubsystem<UProvincesMap>();
	
	const TArray<int32>& Positions = ProvincesMap->GetProvincePositions(Color);
	const FVector2d SizeVector = ProvincesMap->GetSizeVector();

	for (const auto& Position : Positions)
	{
		ProvinceCenters[Color] += FTextureUtils::GetPositionVector(Position, SizeVector);
	}

	ProvinceCenters[Color] = ProvinceCenters[Color] / Positions.Num() / SizeVector;
}

void UObjectMap::Clear()
{
	ProvinceCenters.Empty();
}

void UObjectMap::Init(UScenario* Scenario)
{
	for (const auto& Province : GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces())
	{
		CalculateProvinceCenter(Province->GetId());
	}
}

void UObjectMap::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

FVector2d UObjectMap::GetProvinceCenter(const FColor& Color)
{
	return ProvinceCenters[Color];
}