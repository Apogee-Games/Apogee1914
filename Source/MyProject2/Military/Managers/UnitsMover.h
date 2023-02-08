#pragma once
#include "MyProject2/Maps/Graph.h"
#include "MyProject2/Military/Instances/Unit.h"

#include "UnitsMover.generated.h"


UCLASS()
class UUnitsMover: public UWorldSubsystem
{
	GENERATED_BODY()

public:
	
	FGraph* GetGraph() const;

	void SetGraph(FGraph* NewGraph);

	virtual void MoveUnit(UUnit* Unit, const FColor& Province);

	virtual int Estimate(UUnit* Unit, const FColor& Province);

	virtual void Tick();
	
private:
	FGraph* Graph = nullptr;

	TMap<UUnit*, TArray<TPair<FColor, int>>> Paths;

	TMap<UUnit*, int> Positions;
};
