#pragma once

class UProvince;

class FGraph
{
public:
	explicit FGraph(const TMap<UProvince*, TSet<UProvince*>>& AdjacencyList);

	TArray<TPair<UProvince*, int>> FindPath(UProvince* From, UProvince* To);

private:
	TMap<UProvince*, TSet<UProvince*>> AdjacencyList;
};
