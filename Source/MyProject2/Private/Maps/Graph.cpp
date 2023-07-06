
#include "Maps/Graph.h"

#include "Administration/Instances/Province.h"
#include <set>
#include <map>

FGraph::FGraph()
{
}

FGraph::FGraph(const TMap<UProvince*, TSet<UProvince*>>& AdjacencyList, UMapsDataGatherer* DataGatherer): AdjacencyList(AdjacencyList), DataGatherer(DataGatherer)
{
}

TArray<FPathElement> FGraph::FindPath(UProvince* From, UProvince* To)
{
	return FindPathInternal(From, To);
}

TArray<FPathElement> FGraph::CreateRetreatPath(UProvince* From, UCountry* Country)
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

TArray<FPathElement> FGraph::FindPathInternal(UProvince* From, UProvince* To)
{
	std::set<std::pair<int32, UProvince*>> queue;
	std::map<UProvince*, UProvince*> paths;
	std::map<UProvince*, int32> distances;

	queue.insert({0, From});
	distances.insert({From, 0});
	
	while (!queue.empty())
	{
		UProvince* Province = queue.begin()->second;
		queue.erase(queue.begin());

		if (Province == To)
		{
			TArray<FPathElement> PathElements;
			while (From != Province)
			{
				UProvince* Previous = paths[Province];
				PathElements.Insert({Province, 5}, 0);
				Province = Previous;
			}
			return PathElements;
		}

		int32 ProvinceDistance = distances[Province];
		
		for (const auto& Neightbour: AdjacencyList[Province])
		{
			if (!distances.count(Neightbour) || ProvinceDistance + 5 < distances[Neightbour]) // TODO: Proper distance calculation
			{
				FVector2d VectorBetweenCenters = DataGatherer->GetProvinceCenter(To->GetId()) - DataGatherer->GetProvinceCenter(Neightbour->GetId());
				int32 Expectancy = VectorBetweenCenters.Length() / 100; // TODO: Think how to calculate scale better
				distances[Neightbour] = ProvinceDistance + 5;
				paths[Neightbour] = Province;

				queue.insert({ProvinceDistance + Expectancy, Neightbour});
			}
		}
	}

	return {};
}
