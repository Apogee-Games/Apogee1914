#include "CountriesMap.h"

#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Utils/TextureUtils.h"

void UCountriesMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");
	CountriesMapTexture = FTextureUtils::LoadTexture("/Game/maps/country");
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

void UCountriesMap::UpdateCountriesMapColors() const
{
	UCountriesManager* CountriesManager = GetWorld()->GetSubsystem<UCountriesManager>();

	const FColor* ProvincesColors = FTextureUtils::GetPixels(ProvincesMapTexture, LOCK_READ_ONLY);

	FColor* CountriesColors = FTextureUtils::GetPixels(CountriesMapTexture, LOCK_READ_WRITE);

	const int Size = SizeVector.X * SizeVector.Y;

	const TArray<int> Borders = FindProvincesBorders(ProvincesColors, SizeVector.X, SizeVector.Y, CountriesManager);
	const int* Distances = FindDistancesFromBorders(Borders, SizeVector.X, SizeVector.Y);

	for (int i = 0; i < Size; ++i)
	{
		if (!CountriesManager->ExistsCountryWithSuchProvince(ProvincesColors[i]))
		{
			CountriesColors[i] = FColor(0, 0, 0, 0);
			continue;
		}

		FVector2D Position = FTextureUtils::GetPositionVector(i, SizeVector);

		const FColor* Color = GetColor(Position, ProvincesColors[i], CountriesManager);

		if (Color)
		{
			CountriesColors[i] = Color->WithAlpha(255 - FMath::Min(10, Distances[i] + 1) * 10);
		}
	}

	FTextureUtils::UnlockPixels(CountriesMapTexture);

	FTextureUtils::UnlockPixels(ProvincesMapTexture);

	CountriesMapTexture->UpdateResource();

	delete Distances;
}

void UCountriesMap::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	UpdateCountriesMapColors();
}

TArray<int> UCountriesMap::FindProvincesBorders(const FColor* ProvincesColor, const int Width, const int Height,
                                                UCountriesManager* CountriesManager) const
{
	TArray<int> Borders;
	const int Size = Width * Height;
	for (int i = 0; i < Size; ++i)
	{
		const int y = i / static_cast<int>(SizeVector.Y);
		const int x = i % static_cast<int>(SizeVector.Y);

		if (x > 0 && !CountriesManager->AreProvincesControlledBySameCountry(ProvincesColor[i], ProvincesColor[i - 1]))
		{
			Borders.Add(i);
			continue;
		}
		if (x + 1 < Width && !CountriesManager->AreProvincesControlledBySameCountry(
			ProvincesColor[i], ProvincesColor[i + 1]))
		{
			Borders.Add(i);
			continue;
		}
		if (y > 0 && !CountriesManager->AreProvincesControlledBySameCountry(
			ProvincesColor[i], ProvincesColor[i - Width]))
		{
			Borders.Add(i);
			continue;
		}
		if (y + 1 < Height && !CountriesManager->AreProvincesControlledBySameCountry(
			ProvincesColor[i], ProvincesColor[i + Width]))
		{
			Borders.Add(i);
			continue;
		}
	}
	return Borders;
}

int* UCountriesMap::FindDistancesFromBorders(const TArray<int>& Borders, const int Width, const int Height) const
{
	const int Size = Width * Height;

	int* Distances = new int[Size];

	for (int i = 0; i < Size; ++i)
	{
		Distances[i] = INT_MAX;
	}

	TQueue<int> Queue;
	for (const auto& Point : Borders)
	{
		Queue.Enqueue(Point);
		Distances[Point] = 0;
	}

	while (!Queue.IsEmpty())
	{
		int Point;
		Queue.Dequeue(Point);

		const int y = Point / static_cast<int>(SizeVector.Y);
		const int x = Point % static_cast<int>(SizeVector.Y);

		if (x > 0 && Distances[Point - 1] > Distances[Point] + 1)
		{
			Distances[Point - 1] = Distances[Point] + 1;
			Queue.Enqueue(Point - 1);
		}
		if (x + 1 < Width && Distances[Point + 1] > Distances[Point] + 1)
		{
			Distances[Point + 1] = Distances[Point] + 1;
			Queue.Enqueue(Point + 1);
		}
		if (y > 0 && Distances[Point - Width] > Distances[Point])
		{
			Distances[Point - Width] = Distances[Point] + 1;
			Queue.Enqueue(Point - Width);
		}
		if (y + 1 < Height && Distances[Point + Width] > Distances[Point])
		{
			Distances[Point + Width] = Distances[Point] + 1;
			Queue.Enqueue(Point + Width);
		}
	}
	return Distances;
}

const FColor* UCountriesMap::GetColor(const FVector2D& Position, const FColor& ProvinceColor,
                                      UCountriesManager* CountriesManager) const
{
	return FMath::Abs<int>(Position.X - Position.Y) % (2 * CrossLineWidth) < CrossLineWidth
		       ? CountriesManager->GetControllerCountryColor(ProvinceColor)
		       : CountriesManager->GetOwnerCountryColor(ProvinceColor);
}
