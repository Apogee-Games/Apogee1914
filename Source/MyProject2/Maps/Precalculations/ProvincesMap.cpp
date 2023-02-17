#include "ProvincesMap.h"

#include "DistanceCalculator.h"
#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Administration/Managers/StateManager.h"
#include "MyProject2/Utils/TextureUtils.h"

void UProvincesMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

void UProvincesMap::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	PositionColor = new FColor[SizeVector.X * SizeVector.Y];
	ProvincesDistances = new int32[SizeVector.X * SizeVector.Y];
	StatesDistances = new int32[SizeVector.X * SizeVector.Y];
	CountriesDistances = new int32[SizeVector.X * SizeVector.Y];

	CalculateMappers(ProvincesMapTexture);
	
	CalculateDistances();

	FindNeighbours();

	CalculateBoxes();

	bIsFullyInitialized = true;
	PerformOnFullInitializationActions();
}

FVector2d UProvincesMap::GetSizeVector() const
{
	return SizeVector;
}

void UProvincesMap::CalculateDistances() const
{
	TArray<FRunnableThread*> Threads;
	
	Threads.Add(CalculateProvincesDistances());
	
	Threads.Add(CalculateStatesDistances());
	
	Threads.Add(CalculateCountriesDistances());
	
	for (const auto& Thread: Threads)
	{
		Thread->WaitForCompletion();
	}
}

const FColor& UProvincesMap::GetColor(int32 Position) const
{
	return PositionColor[Position];
}

const TArray<int32>& UProvincesMap::GetProvincePositions(const FColor& Color) const
{
	return ColorPosition[Color];
}

int UProvincesMap::GetProvincesDistance(int Position) const
{
	return ProvincesDistances[Position];
}

const int* UProvincesMap::GetProvincesDistances() const
{
	return ProvincesDistances;
}

const int* UProvincesMap::GetStatesDistances() const
{
	return StatesDistances;
}

const int* UProvincesMap::GetCountriesDistances() const
{
	return CountriesDistances;
}

const TArray<FProvincesBox>& UProvincesMap::GetBoxes() const
{
	return Boxes;
}

int UProvincesMap::GetStatesDistance(int Position) const
{
	return StatesDistances[Position];
}

int UProvincesMap::GetCountriesDistance(int Position) const
{
	return CountriesDistances[Position];
}

void UProvincesMap::Deinitialize()
{
	delete[] ProvincesDistances;
	delete[] StatesDistances;
	delete[] CountriesDistances;
	delete[] PositionColor;
	Super::Deinitialize();
}

void UProvincesMap::CalculateMappers(UTexture2D* ProvinceMap)
{
	FColor* Pixel = FTextureUtils::GetPixels(ProvinceMap, LOCK_READ_WRITE);
	
	for (int i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		PositionColor[i] = FColor(Pixel[i].R, Pixel[i].G, Pixel[i].B, Pixel[i].A);
		if (!ColorPosition.Contains(PositionColor[i])) {
			ColorPosition.Add(PositionColor[i], TArray<int32>());
		}
		ColorPosition[PositionColor[i]].Add(i);
	}

	FTextureUtils::UnlockPixels(ProvinceMap);
}

void UProvincesMap::FindNeighbours()
{
	for (const auto& [Color, Positions]: ColorPosition)
	{
		Neighbours.Add(Color);	
	}
	
	for (int i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		const int y = i / static_cast<int>(SizeVector.Y);
		const int x = i % static_cast<int>(SizeVector.Y);
		
		if (x > 0 && PositionColor[i] != PositionColor[i - 1])
		{
			Neighbours[PositionColor[i]].Add(PositionColor[i - 1]);
			Neighbours[PositionColor[i - 1]].Add(PositionColor[i]);
		}
		if (x + 1 < SizeVector.X && PositionColor[i] != PositionColor[i + 1])
		{
			Neighbours[PositionColor[i]].Add(PositionColor[i + 1]);
			Neighbours[PositionColor[i + 1]].Add(PositionColor[i]);
		}
		if (y > 0 && PositionColor[i] != PositionColor[i - static_cast<int>(SizeVector.X)])
		{
			Neighbours[PositionColor[i]].Add(PositionColor[i - static_cast<int>(SizeVector.X)]);
			Neighbours[PositionColor[i - static_cast<int>(SizeVector.X)]].Add(PositionColor[i]);
		}
		if (y + 1 < SizeVector.Y && PositionColor[i] != PositionColor[i + static_cast<int>(SizeVector.X)])
		{
			Neighbours[PositionColor[i]].Add(PositionColor[i + static_cast<int>(SizeVector.X)]);
			Neighbours[PositionColor[i + static_cast<int>(SizeVector.X)]].Add(PositionColor[i]);
		}
	}
}

void UProvincesMap::CalculateBoxes()
{
	UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	for (const auto& [From, Tos]: Neighbours)
	{
		UProvince* Province = ProvinceManager->GetProvince(From);
		if (!Province || ProvinceBox.Contains(Province)) continue;
		FProvincesBox Box = FProvincesBox(this, Province->GetCountryController());
		AddProvincesToBox(Box, Province, Province->GetCountryController(), ProvinceManager);
		Boxes.Add(Box);
	}
}

void UProvincesMap::AddProvincesToBox(FProvincesBox& Box, UProvince* FromProvince, UCountry* Country, UProvinceManager* ProvinceManager)
{
	Box.AddProvince(FromProvince);
	ProvinceBox.Add(FromProvince, Box);
	for (const auto& To: Neighbours[FromProvince->GetId()])
	{
		UProvince* ToProvince = ProvinceManager->GetProvince(To);
		if (!ToProvince || ToProvince->GetCountryController() != Country || ProvinceBox.Contains(ToProvince)) continue;
		AddProvincesToBox(Box, ToProvince, Country, ProvinceManager);
	}
}

FRunnableThread* UProvincesMap::CalculateProvincesDistances() const
{
	FDistanceCalculator* DistanceCalculator = new FDistanceCalculator(ProvincesDistances, SizeVector);

	for (int i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		ProvincesDistances[i] = INT32_MAX;
		
		const int y = i / static_cast<int>(SizeVector.Y);
		const int x = i % static_cast<int>(SizeVector.Y);
		
		if (x > 0 && PositionColor[i] != PositionColor[i - 1])
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (x + 1 < SizeVector.X && PositionColor[i] != PositionColor[i + 1])
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (y > 0 && PositionColor[i] != PositionColor[i - static_cast<int>(SizeVector.X)])
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (y + 1 < SizeVector.Y && PositionColor[i] != PositionColor[i + static_cast<int>(SizeVector.X)])
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
	}
	
	return FRunnableThread::Create(DistanceCalculator, TEXT("Province Distances Calculation"));
}

FRunnableThread* UProvincesMap::CalculateStatesDistances() const
{
	FDistanceCalculator* DistanceCalculator = new FDistanceCalculator(StatesDistances, SizeVector);

	UStateManager* StateManager = GetWorld()->GetSubsystem<UStateManager>();
	
	for (int i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		StatesDistances[i] = INT32_MAX;
		
		const int y = i / static_cast<int>(SizeVector.Y);
		const int x = i % static_cast<int>(SizeVector.Y);
		
		if (x > 0 && PositionColor[i] != PositionColor[i - 1]
		&& StateManager->AreProvincesNotInTheSameState(PositionColor[i], PositionColor[i - 1]))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (x + 1 < SizeVector.X && PositionColor[i] != PositionColor[i + 1]
		&& StateManager->AreProvincesNotInTheSameState(PositionColor[i], PositionColor[i + 1]))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (y > 0 && PositionColor[i] != PositionColor[i - static_cast<int>(SizeVector.X)]
		&& StateManager->AreProvincesNotInTheSameState(PositionColor[i], PositionColor[i - static_cast<int>(SizeVector.X)]))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (y + 1 < SizeVector.Y && PositionColor[i] != PositionColor[i + static_cast<int>(SizeVector.X)]
		&& StateManager->AreProvincesNotInTheSameState(PositionColor[i], PositionColor[i + static_cast<int>(SizeVector.X)]))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
	}
	
	return FRunnableThread::Create(DistanceCalculator, TEXT("States Distances Calculation"));
}

FRunnableThread* UProvincesMap::CalculateCountriesDistances() const
{
	FDistanceCalculator* DistanceCalculator = new FDistanceCalculator(CountriesDistances, SizeVector);

	UCountriesManager* CountriesManager = GetWorld()->GetSubsystem<UCountriesManager>();
	
	for (int i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		CountriesDistances[i] = INT32_MAX;
		
		const int y = i / static_cast<int>(SizeVector.Y);
		const int x = i % static_cast<int>(SizeVector.Y);
		
		if (x > 0 && PositionColor[i] != PositionColor[i - 1]
		&& !CountriesManager->AreProvincesControlledBySameCountry(PositionColor[i], PositionColor[i - 1]))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (x + 1 < SizeVector.X && PositionColor[i] != PositionColor[i + 1]
		&& !CountriesManager->AreProvincesControlledBySameCountry(PositionColor[i], PositionColor[i + 1]))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (y > 0 && PositionColor[i] != PositionColor[i - static_cast<int>(SizeVector.X)]
		&& !CountriesManager->AreProvincesControlledBySameCountry(PositionColor[i], PositionColor[i - static_cast<int>(SizeVector.X)]))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (y + 1 < SizeVector.Y && PositionColor[i] != PositionColor[i + static_cast<int>(SizeVector.X)]
		&& !CountriesManager->AreProvincesControlledBySameCountry(PositionColor[i], PositionColor[i + static_cast<int>(SizeVector.X)]))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
	}

	return FRunnableThread::Create(DistanceCalculator, TEXT("Countries Distances Calculation"));
}
