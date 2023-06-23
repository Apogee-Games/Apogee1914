
#include "Maps/Precalculations/Distances/DistancesMap.h"

#include "Administration/Managers/CountriesManager.h"
#include "Administration/Managers/StateManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Maps/Precalculations/Distances/DistanceCalculator.h"


void UDistancesMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//TODO: GetGameInstance()->GetSubsystem<UProvinceManager>()->AddProvinceOwningCountryObserver(this);
}

void UDistancesMap::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
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

ELoadStage UDistancesMap::GetLoadStage()
{
	return ELoadStage::DistancesMap;
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
	return GetDistanceCalculator(GetGameInstance()->GetSubsystem<UStateManager>(),
								 &UStateManager::AreProvincesNotInTheSameState,
								 StatesDistances,
								 TEXT("States Distances Calculation"));
}

FRunnableThread* UDistancesMap::CalculateCountriesDistances() 
{
	return GetDistanceCalculator(GetGameInstance()->GetSubsystem<UCountriesManager>(),
	                             &UCountriesManager::AreProvincesOwnedByDifferentCountry,
	                             CountriesDistances,
	                             TEXT("Countries Distances Calculation"));
}

FRunnableThread* UDistancesMap::GetDistanceCalculator(UObject* Object,
                                                      bool (UObject::*Func)(const FColor&, const FColor&) const,
                                                      TArray<int32>& Distance, TCHAR* Name)
{
	FDistanceCalculator* DistanceCalculator = new FDistanceCalculator(Distance, SizeVector, Depth);
	const TArray<FColor>& Colors = GetGameInstance()->GetSubsystem<UProvincesMap>()->GetColors();

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

void UDistancesMap::Init(UScenario* Scenario)
{
	SizeVector = GetGameInstance()->GetSubsystem<UProvincesMap>()->GetSizeVector();

	ProvincesDistances.SetNum(SizeVector.X * SizeVector.Y);
	StatesDistances.SetNum(SizeVector.X * SizeVector.Y);
	CountriesDistances.SetNum(SizeVector.X * SizeVector.Y);

	CalculateDistances();
}

void UDistancesMap::Clear()
{
	ProvincesDistances.Empty();
	StatesDistances.Empty();
	CountriesDistances.Empty();
}