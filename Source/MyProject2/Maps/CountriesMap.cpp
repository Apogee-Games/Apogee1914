#include "CountriesMap.h"

#include "MyProject2/Utils/TextureUtils.h"

FCountriesMap::FCountriesMap(): GameState(nullptr), CountriesMapTexture(nullptr), ProvincesMapTexture(nullptr)
{
}

FCountriesMap::FCountriesMap(AMyGameState* GameState):
	GameState(GameState),
	CountriesMapTexture(GameState->GetCountriesMapTexture()),
	ProvincesMapTexture(GameState->GetProvincesMapTexture())
{
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

FCountriesMap::FCountriesMap(UTexture2D* CountriesMapTexture, UTexture2D* ProvincesMapTexture, AMyGameState* GameState):
	GameState(GameState), CountriesMapTexture(CountriesMapTexture), ProvincesMapTexture(ProvincesMapTexture)
{
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

void FCountriesMap::UpdateCountriesMapColors() const
{
	const FColor* ProvincesColors = FTextureUtils::GetPixels(ProvincesMapTexture, LOCK_READ_ONLY);

	FColor* CountriesColors = FTextureUtils::GetPixels(CountriesMapTexture, LOCK_READ_WRITE);

	const int Size = SizeVector.X * SizeVector.Y;

	const TArray<int> Borders = FindProvincesBorders(ProvincesColors, SizeVector.X, SizeVector.Y);
	const int* Distances = FindDistancesFromBorders(Borders, SizeVector.X, SizeVector.Y);

	for (int i = 0; i < Size; ++i)
	{
		if (!GameState->ExistsCountryWithSuchProvince(ProvincesColors[i])) CountriesColors[i] = FColor(0, 0, 0, 0);
		else CountriesColors[i] = GameState->GetCountryColor(ProvincesColors[i]).WithAlpha(255 - FMath::Min(10, Distances[i] + 1) * 10);
	}

	FTextureUtils::UnlockPixels(CountriesMapTexture);

	FTextureUtils::UnlockPixels(ProvincesMapTexture);

	CountriesMapTexture->UpdateResource();

	delete Distances;
}

TArray<int> FCountriesMap::FindProvincesBorders(const FColor* ProvincesColor, const int Width, const int Height) const
{
	TArray<int> Borders;
	const int Size = Width * Height;
	for (int i = 0; i < Size; ++i)
	{
		const int y = i / static_cast<int>(SizeVector.Y);
		const int x = i % static_cast<int>(SizeVector.Y);

		if (x > 0 && GameState->GetCountryColor(ProvincesColor[i]) != GameState->GetCountryColor(ProvincesColor[i - 1])) {
			Borders.Add(i);
			continue;
		}
		if (x + 1 < Width && GameState->GetCountryColor(ProvincesColor[i]) != GameState->GetCountryColor(ProvincesColor[i + 1])) {
			Borders.Add(i);
			continue;
		}
		if (y > 0 && GameState->GetCountryColor(ProvincesColor[i]) != GameState->GetCountryColor(ProvincesColor[i - Width])) {
			Borders.Add(i);
			continue;
		}
		if (y + 1 < Height && GameState->GetCountryColor(ProvincesColor[i]) != GameState->GetCountryColor(ProvincesColor[i + Width])) {
			Borders.Add(i);
			continue;
		}
	}
	return Borders;
}

int* FCountriesMap::FindDistancesFromBorders(const TArray<int>& Borders, const int Width, const int Height) const
{
	const int Size = Width * Height;
	
	int* Distances = new int[Size];
	
	for (int i = 0; i < Size; ++i)
	{
		Distances[i] = INT_MAX;
	}
	
	TQueue<int> Queue;
	for (const auto& Point: Borders)
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

		if (x > 0 && Distances[Point - 1] > Distances[Point] + 1) {
			Distances[Point - 1] = Distances[Point] + 1;
			Queue.Enqueue(Point - 1);
		}
		if (x + 1 < Width && Distances[Point + 1] > Distances[Point] + 1) {
			Distances[Point + 1] = Distances[Point] + 1;
			Queue.Enqueue(Point + 1);
		}
		if (y > 0 && Distances[Point - Width] > Distances[Point]) {
			Distances[Point - Width] = Distances[Point] + 1;
			Queue.Enqueue(Point - Width);
		}
		if (y + 1 < Height && Distances[Point + Width] > Distances[Point]) {
			Distances[Point + Width] = Distances[Point] + 1;
			Queue.Enqueue(Point + Width);
		}
	}
	return Distances;
}