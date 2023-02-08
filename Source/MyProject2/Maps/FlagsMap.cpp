#include "FlagsMap.h"

#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Utils/TextureUtils.h"

void UFlagsMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");
	FlagsMapTexture = FTextureUtils::LoadTexture("/Game/maps/flags");
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}


TMap<FString, FVector4> UFlagsMap::FindCountriesBoxes(const FColor* ProvincesColors)
{
	UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();

	TMap<FString, FVector4> Boxes;
	const int Size = SizeVector.X * SizeVector.Y;
	for (int i = 0; i < Size; ++i)
	{
		const UProvince* Province = ProvinceManager->GetProvince(ProvincesColors[i]);
		if (!Province) continue;

		
		
		const FVector2d Position = FTextureUtils::GetPositionVector(i, SizeVector);
		if (Boxes.Contains(Province->GetOwnerCountryTag()))
		{
			const FVector4 Box = Boxes[Province->GetOwnerCountryTag()];
			Boxes.Add(Province->GetOwnerCountryTag(), UpdateBox(Box, Position));
		}
		else
		{
			Boxes.Add(Province->GetOwnerCountryTag(),
			          FVector4(Position.X, Position.Y, Position.X, Position.Y));
		}
	}
	return Boxes;
}

FVector2d UFlagsMap::GetRelativePosition(const FVector2d& Position, const FVector4& Box)
{
	const FVector2d MovedPosition = FVector2d(Position.X - Box.X, Position.Y - Box.Y);

	return FVector2d(MovedPosition.X / (Box.Z - Box.X), MovedPosition.Y / (Box.W - Box.Y));
}

FColor UFlagsMap::GetFlagColor(UTexture2D* Flag, const FVector2d& RelativePosition)
{
	const FColor* FlagColors = FTextureUtils::GetPixels(Flag, LOCK_READ_ONLY);

	const FVector2d FlagSizeVector = FTextureUtils::GetTextureSizeVector(Flag);

	const FVector2d FlagPosition = RelativePosition * FlagSizeVector;

	const int Position = FTextureUtils::GetPixelPosition(FlagPosition, FlagSizeVector);

	const FColor Color = FlagColors[Position];

	FTextureUtils::UnlockPixels(Flag);

	return Color;
}

FVector4 UFlagsMap::UpdateBox(const FVector4& Box, const FVector2d& Position)
{
	return FVector4(FMath::Min(Box.X, Position.X), FMath::Min(Box.Y, Position.Y),
	                FMath::Max(Box.Z, Position.X), FMath::Max(Box.W, Position.Y));
}


void UFlagsMap::UpdateFlagsMapColors()
{
	UCountriesManager* CountriesManager = GetWorld()->GetSubsystem<UCountriesManager>();
	UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();

	const FColor* ProvincesColors = FTextureUtils::GetPixels(ProvincesMapTexture, LOCK_READ_ONLY);

	FColor* FlagsColors = FTextureUtils::GetPixels(FlagsMapTexture, LOCK_READ_WRITE);

	TMap<FString, FVector4> Boxes = FindCountriesBoxes(ProvincesColors);

	const int Size = SizeVector.X * SizeVector.Y;

	for (int i = 0; i < Size; ++i)
	{
		const UProvince* Province = ProvinceManager->GetProvince(ProvincesColors[i]);
		if (!Province) continue;

		const FVector4 Box = Boxes[Province->GetOwnerCountryTag()];

		const FVector2d Position = FTextureUtils::GetPositionVector(i, SizeVector);

		FVector2d RelativePosition = GetRelativePosition(Position, Box);

		UCountry* Country = CountriesManager->GetCountry(Province->GetOwnerCountryTag());

		UTexture2D* Flag = Country->GetFlag();

		FlagsColors[i] = GetFlagColor(Flag, RelativePosition);
	}

	FTextureUtils::UnlockPixels(ProvincesMapTexture);

	FTextureUtils::UnlockPixels(FlagsMapTexture);

	FlagsMapTexture->UpdateResource();
}
