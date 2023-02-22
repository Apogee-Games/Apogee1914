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

	ProvincesDistances.SetNum(SizeVector.X * SizeVector.Y);
	StatesDistances.SetNum(SizeVector.X * SizeVector.Y);
	CountriesDistances.SetNum(SizeVector.X * SizeVector.Y);

	CalculateDistances();

	bIsFullyInitialized = true;
	PerformOnFullInitializationActions();
}


int32 UDistancesMap::GetProvincesDistance(int32 Position) const
{
	return ProvincesDistances[Position];
}

int32 UDistancesMap::GetStatesDistance(int32 Position) const
{
	return StatesDistances[Position];
}

int32 UDistancesMap::GetCountriesDistance(int32 Position) const
{
	return CountriesDistances[Position];
}

const TArray<int32>& UDistancesMap::GetProvincesDistances() const
{
	return ProvincesDistances;
}

const TArray<int32>& UDistancesMap::GetStatesDistances() const
{
	return StatesDistances;
}

const TArray<int32>& UDistancesMap::GetCountriesDistances() const
{
	return CountriesDistances;
}

void UDistancesMap::ProvinceHasNewOwningCountry(UProvince* Province)
{
	CalculateCountriesDistances()->WaitForCompletion();
}

void UDistancesMap::CalculateDistances()
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

FRunnableThread* UDistancesMap::CalculateProvincesDistances()
{
	return GetDistanceCalculator(nullptr,
								 nullptr,
								 ProvincesDistances,
								 TEXT("Province Distances Calculation"));
}

FRunnableThread* UDistancesMap::CalculateStatesDistances()
{
	return GetDistanceCalculator(GetWorld()->GetSubsystem<UStateManager>(),
								 &UStateManager::AreProvincesNotInTheSameState,
								 StatesDistances,
								 TEXT("States Distances Calculation"));
}

FRunnableThread* UDistancesMap::CalculateCountriesDistances() 
{
	return GetDistanceCalculator(GetWorld()->GetSubsystem<UCountriesManager>(),
	                             &UCountriesManager::AreProvincesOwnedByDifferentCountry,
	                             CountriesDistances,
	                             TEXT("Countries Distances Calculation"));
}

FRunnableThread* UDistancesMap::GetDistanceCalculator(UObject* Object,
                                                      bool (UObject::*Func)(const FColor&, const FColor&) const,
                                                      TArray<int32>& Distance, TCHAR* Name)
{
	FDistanceCalculator* DistanceCalculator = new FDistanceCalculator(Distance, SizeVector, Depth);
	const TArray<FColor>& Colors = GetWorld()->GetSubsystem<UProvincesMap>()->GetColors();

	const int32 Width = static_cast<int32>(SizeVector.X);
	const int32 Height = static_cast<int32>(SizeVector.Y);

	for (int32 i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		Distance[i] = Depth;

		const int32 y = i / Width;
		const int32 x = i % Width;

		if (x > 0 && Colors[i] != Colors[i - 1] && (!Object || !Func || (Object->*Func)(Colors[i], Colors[i - 1])))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (x + 1 < Width && Colors[i] != Colors[i + 1] && (!Object || !Func || (Object->*Func)(Colors[i], Colors[i + 1])))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (y > 0 && Colors[i] != Colors[i - Width] && (!Object || !Func || (Object->*Func)(Colors[i], Colors[i - Width])))
		{
			DistanceCalculator->AddStartPoint(i);
			continue;
		}
		if (y + 1 < Height && Colors[i] != Colors[i + Width] && (!Object || !Func || (Object->*Func)(Colors[i], Colors[i + Width])))
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
