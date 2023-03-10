
#include "Maps/Graph.h"

#include "Administration/Instances/Province.h"

FGraph::FGraph(const TMap<UProvince*, TSet<UProvince*>>& AdjacencyList): AdjacencyList(AdjacencyList)
{
}

const TArray<TPair<UProvince*, int>> FGraph::FindPath(UProvince* From, UProvince* To)
{
	return {{To, 1}};
}
