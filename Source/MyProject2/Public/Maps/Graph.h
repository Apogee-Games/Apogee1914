#pragma once
#include "MapsDataGatherer.h"

class UProvince;

struct FPathElement
{
	UProvince* To;
	int32 Cost;
};

class FGraph
{
public:
	FGraph();

	FGraph(const TMap<UProvince*, TSet<UProvince*>>& AdjacencyList, UMapsDataGatherer* DataGatherer);

	TArray<FPathElement> FindPath(UProvince* From, UProvince* To);

	TArray<FPathElement> CreateRetreatPath(UProvince* From, UCountry* Country);
private:
	TMap<UProvince*, TSet<UProvince*>> AdjacencyList;

	UMapsDataGatherer* DataGatherer;

	TArray<FPathElement> FindPathInternal(UProvince* From, UProvince* To);
};
