#include "DistancesMap.h"

#include "DistanceCalculator.h"
#include "MyProject2/Administration/Managers/StateManager.h"
#include "MyProject2/Maps/Precalculations/ProvincesMap.h"

void UDistancesMap::OnWorldBeginPlay(UWorld& InWorld)
{
	UWorldSubsystem::OnWorldBeginPlay(InWorld);

	GetWorld()->GetSubsystem<UProvincesMap>()->RegisterOnFullInitializationAction(this, &UDistancesMap::Init);
	//TODO: GetWorld()->GetSubsystem<UProvinceManager>()->AddProvinceOwningCountryObserver(this);
}

void UDistancesMap::Init()
{
	SizeVector = GetWorld()->GetSubsystem<UProvincesMap>()->GetSizeVector();

	ProvincesDistances = new int32[SizeVector.X * SizeVector.Y];
	StatesDistances = new int32[SizeVector.X * SizeVector.Y];
	CountriesDistances = new int32[SizeVector.X * SizeVector.Y];

	CalculateDistances();

	bIsFullyInitialized = true;
	PerformOnFullInitializationActions();
}


int UDistancesMap::GetProvincesDistance(int Position) const
{
	return ProvincesDistances[Position];
}

int UDistancesMap::GetStatesDistance(int Position) const
{
	return StatesDistances[Position];
}

int UDistancesMap::GetCountriesDistance(int Position) const
{
	return CountriesDistances[Position];
}

const int* UDistancesMap::GetProvincesDistances() const
{
	return ProvincesDistances;
}

const int* UDistancesMap::GetStatesDistances() const
{
	return StatesDistances;
}

const int* UDistancesMap::GetCountriesDistances() const
{
	return CountriesDistances;
}

void UDistancesMap::Deinitialize()
{
	delete[] ProvincesDistances;
	delete[] StatesDistances;
	delete[] CountriesDistances;
	UWorldSubsystem::Deinitialize();
}

void UDistancesMap::ProvinceHasNewOwningCountry(UProvince* Province)
{
	CalculateCountriesDistances()->WaitForCompletion();
}

void UDistancesMap::CalculateDistances() const
{
	TArray<FRunnableThread*> Threads;

	Threads.Add(CalculateProvincesDistances());

	Threads.Add(CalculateStatesDistances());

	Threads.Add(CalculateCountriesDistances());

	for (const auto& Thread : Threads)
	{
		Thread->WaitForCompletion();
	}
}

FRunnableThread* UDistancesMap::CalculateProvincesDistances() const
{
	return GetDistanceCalculator(nullptr,
								 nullptr,
								 ProvincesDistances,
								 TEXT("Province Distances Calculation"));
}

FRunnableThread* UDistancesMap::CalculateStatesDistances() const
{
	return GetDistanceCalculator(GetWorld()->GetSubsystem<UStateManager>(),
								 &UStateManager::AreProvincesNotInTheSameState,
								 StatesDistances,
								 TEXT("States Distances Calculation"));
}

FRunnableThread* UDistancesMap::CalculateCountriesDistances() const
{
	return GetDistanceCalculator(GetWorld()->GetSubsystem<UCountriesManager>(),
	                             &UCountriesManager::AreProvincesOwnedByDifferentCountry,
	                             CountriesDistances,
	                             TEXT("Countries Distances Calculation"));
}

FRunnableThread* UDistancesMap::GetDistanceCalculator(UObject* Object,
                                                      bool (UObject::*Func)(const FColor&, const FColor&) const,
                                                      int* Distance, TCHAR* Name) const
{
	FDistanceCalculator* DistanceCalculator = new FDistanceCalculator(Distance, SizeVector, Depth);
	const FColor* Colors = GetWorld()->GetSubsystem<UProvincesMap>()->GetColors();

	for (int i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		Distance[i] = Depth;

		const int y = i / static_cast<int>(SizeVector.Y);
		const int x = i % static_cast<int>(SizeVector.Y);

		if (x > 0 && Colors[i] != Colors[i - 1]
			&& (!Object || !Func || (Object->*Func)(Colors[i], Colors[i - 1])))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (x + 1 < SizeVector.X && Colors[i] != Colors[i + 1]
			&& (!Object || !Func || (Object->*Func)(Colors[i], Colors[i + 1])))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (y > 0 && Colors[i] != Colors[i - static_cast<int>(SizeVector.X)]
			&& (!Object || !Func || (Object->*Func)(Colors[i], Colors[i - static_cast<int>(SizeVector.X)])))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (y + 1 < SizeVector.Y && Colors[i] != Colors[i + static_cast<int>(SizeVector.X)]
			&& (!Object || !Func || (Object->*Func)(Colors[i], Colors[i + static_cast<int>(SizeVector.X)])))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
	}

	return FRunnableThread::Create(DistanceCalculator, Name);
}

/*

FRunnableThread* UProvincesMap::CleanUpCountryDistances(UProvince* Province)
{
FDistanceCleaner* DistanceCleaner = new FDistanceCleaner(CountriesDistances, SizeVector, Depth);
const UCountriesManager* CountriesManager = GetWorld()->GetSubsystem<UCountriesManager>();

DistanceCleaner->AddPossiblePoints(ColorPosition[Province->GetId()]);
for (const auto& NeighbourColor: Neighbours[Province->GetId()])
{
if (CountriesManager->AreProvincesControlledBySameCountry(NeighbourColor, Province->GetId()))
{
DistanceCleaner->AddPossiblePoints(ColorPosition[NeighbourColor]);
}
		
for (const int& i: Borders[{Province->GetId(), NeighbourColor}])
{
DistanceCleaner->AddStartPoint(i);
}
}

return FRunnableThread::Create(DistanceCleaner, TEXT("Distances Cleaning"));
}

FRunnableThread* UProvincesMap::RecalculateCountryDistances(UProvince* Province)
{
FDistanceCalculator* DistanceCalculator = new FDistanceCalculator(CountriesDistances, SizeVector, Depth);
const UCountriesManager* CountriesManager = GetWorld()->GetSubsystem<UCountriesManager>();

for (const auto& NeighbourColor: Neighbours[Province->GetId()])
{
if (!CountriesManager->AreProvincesControlledBySameCountry(NeighbourColor, Province->GetId()))
{
for (const int& i: Borders[{Province->GetId(), NeighbourColor}])
{
DistanceCalculator->AddStartPoint(i);
}
}
}
    
return FRunnableThread::Create(DistanceCalculator, TEXT("Distances Update"));
}

void UProvincesMap::NotifyCountryDistancesUpdateForProvince(UProvince* Province)
{
	TArray<UProvince*> Provinces;

	Provinces.Add(Province);

	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	
	for (const auto& NeighbourColor: Neighbours[Province->GetId()]) {
		Provinces.Add(ProvinceManager->GetProvince(NeighbourColor));
	}
	
	NotifyCountryDistancesUpdate(Provinces);
}

void UProvincesMap::UpdateCountriesDistances(UProvince* Province)
{
	CalculateCountriesDistances()->WaitForCompletion();
}

*/
