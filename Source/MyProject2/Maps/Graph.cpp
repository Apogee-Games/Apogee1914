#include "Graph.h"

FGraph::FGraph(const TMap<FColor, TSet<FColor>>& AdjacencyList): AdjacencyList(AdjacencyList)
{
}

TArray<TPair<FColor, int>> FGraph::FindPath(FColor ProvinceFrom, FColor ProvinceTo)
{
	return {{ProvinceTo, 1}};
}
