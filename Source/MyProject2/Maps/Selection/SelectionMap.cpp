#include "SelectionMap.h"

#include "MyProject2/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Characters/HumanPlayerPawn.h"
#include "MyProject2/Maps/Precalculations/ProvincesMap.h"
#include "MyProject2/Utils/TextureUtils.h"

#define UpdateResource UpdateResource

void USelectionMap::SelectProvince(const FColor& Color)
{
	if (Color == SelectedProvince) return;

	FColor* SelectionMapColors = FTextureUtils::GetPixels(SelectionMapTexture, LOCK_READ_WRITE);

	const UProvincesMap* ProvincesMap = GetWorld()->GetSubsystem<UProvincesMap>();

	if (ProvincesMap->HasProvincePosition(Color))
	{
		for (const auto& i: ProvincesMap->GetProvincePositions(Color))
		{
			SelectionMapColors[i] = SelectedProvinceColor;
		}
	}

	if (ProvincesMap->HasProvincePosition(SelectedProvince))
	{
		for (const auto& i: ProvincesMap->GetProvincePositions(SelectedProvince))
		{
			SelectionMapColors[i] = NonSelectedProvinceColor;
		}
	}
	
	SelectedProvince = Color;

	FTextureUtils::UnlockPixels(SelectionMapTexture);

	SelectionMapTexture->UpdateResource();
}

UProvince* USelectionMap::SelectProvince(const FVector2d& Point)
{
	UProvince* Province = GetProvince(Point);
	if (Province)
	{
		SelectProvince(Province->GetId());
	}
	return Province;
}

FColor USelectionMap::GetProvinceColor(const FVector2d& Point) const
{
	const FVector2d ImagePosition = Point * SizeVector;

	const int Position = FTextureUtils::GetPixelPosition(ImagePosition, SizeVector);

	return GetWorld()->GetSubsystem<UProvincesMap>()->GetColor(Position);
}

void USelectionMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	SelectionMapTexture = FTextureUtils::LoadTexture("/Game/maps/province");
	SizeVector = FTextureUtils::GetTextureSizeVector(SelectionMapTexture);
}

UProvince* USelectionMap::GetProvince(const FVector2d& Point) const
{
	const FColor Color = GetProvinceColor(Point);
	return GetWorld()->GetSubsystem<UProvinceManager>()->GetProvince(Color);
}
