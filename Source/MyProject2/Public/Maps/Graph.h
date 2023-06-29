#pragma once

#include "Administration/Interfaces/Observable/ProvinceOwningCountryObservable.h"

class UProvince;

class FGraph
{
public:
	FGraph();

	explicit FGraph(const TMap<UProvince*, TSet<UProvince*>>& AdjacencyList);

	TArray<TPair<UProvince*, int32>> FindPath(UProvince* From, UProvince* To);

	TArray<TPair<UProvince*, int32>> CreateRetreatPath(UProvince* From, UCountry* Country);
private:
	TMap<UProvince*, TSet<UProvince*>> AdjacencyList;
};
