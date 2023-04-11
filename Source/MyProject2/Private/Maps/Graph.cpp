
#include "Maps/Graph.h"

#include "Administration/Instances/Province.h"

FGraph::FGraph()
{
}

FGraph::FGraph(const TMap<UProvince*, TSet<UProvince*>>& AdjacencyList): AdjacencyList(AdjacencyList)
{
}

TArray<TPair<UProvince*, int>> FGraph::FindPath(UProvince* From, UProvince* To)
{
	return {{To, 5}};
}

TArray<TPair<UProvince*, int32>> FGraph::CreateRetreatPath(UProvince* From, UCountry* Country)
{
	for (const auto& Province: AdjacencyList[From])
	{
		if (Province->GetCountryController() == Country)
		{
			return {{Province, 1}};
		}
	}
	return {};
}
