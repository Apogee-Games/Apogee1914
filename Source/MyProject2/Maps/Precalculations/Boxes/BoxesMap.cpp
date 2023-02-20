#include "BoxesMap.h"

#include "MyProject2/Maps/Precalculations/ProvincesMap.h"
#include "MyProject2/Utils/TextureUtils.h"


void UBoxesMap::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	GetWorld()->GetSubsystem<UProvincesMap>()->RegisterOnFullInitializationAction(this, &UBoxesMap::Init);
	GetWorld()->GetSubsystem<UProvinceManager>()->AddProvinceControllingCountryObserver(this);
}

void UBoxesMap::Init()
{
	SizeVector = GetWorld()->GetSubsystem<UProvincesMap>()->GetSizeVector();

	CalculateProvinceCorners();
	
	CalculateBoxes();

	bIsFullyInitialized = true;
	PerformOnFullInitializationActions();
}


const TArray<FProvincesBox*>& UBoxesMap::GetBoxes() const
{
	return Boxes;
}

const FVector2d& UBoxesMap::GetLeftTopCorner(UProvince* Province) const
{
	return LeftTopCorners[Province];
}

const FVector2d& UBoxesMap::GetRightBottomCorner(UProvince* Province) const
{
	return RightBottomCorners[Province];
}

void UBoxesMap::ProvinceHasNewControllingCountry(UProvince* Province)
{
	RemoveProvinceFromBox(Province);
	
	if (AddProvinceToNeighbourBoxes(Province)) return;

	CreateNewBox(Province);
}


void UBoxesMap::RemoveProvinceFromBox(UProvince* Province)
{
	ProvinceBox[Province]->RemoveProvince(Province);
	if (ProvinceBox[Province]->GetProvinces().IsEmpty())
	{
		Boxes.Remove(ProvinceBox[Province]);
		delete ProvinceBox[Province];
	} else
	{
		NotifyBoxUpdate(ProvinceBox[Province]);
	}
}

bool UBoxesMap::AddProvinceToNeighbourBoxes(UProvince* Province)
{
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	const TSet<FColor>& Neighbours = GetWorld()->GetSubsystem<UProvincesMap>()->GetNeighbours()[Province->GetId()];

	TArray<FProvincesBox*> SameCountryBoxes;

	for (const auto& NeighbourColor: Neighbours)
	{
		const UProvince* Neighbour = ProvinceManager->GetProvince(NeighbourColor);
		if (!Neighbour) continue;
		if (Province->GetCountryController() != Neighbour->GetCountryController()) continue;
		if (ProvinceBox[Neighbour]->GetCountry() != Province->GetCountryController()) continue;
		if (SameCountryBoxes.Contains(ProvinceBox[Neighbour])) continue;
		SameCountryBoxes.Add(ProvinceBox[Neighbour]);
	}

	if (SameCountryBoxes.Num() == 1)
	{
		return AddProvinceToBox(SameCountryBoxes[0], Province);
	}

	if (SameCountryBoxes.Num() > 1)
	{
		return MergeBoxesAndAddProvince(SameCountryBoxes, Province);
	}
	
	return false;
}

bool UBoxesMap::AddProvinceToBox(FProvincesBox* Box, UProvince* Province)
{
	Box->AddProvince(Province);
	ProvinceBox[Province] = Box;
	NotifyBoxUpdate(Box);
	return true;	
}

bool UBoxesMap::MergeBoxesAndAddProvince(TArray<FProvincesBox*>& SameCountryBoxes, UProvince* Province)
{
	SameCountryBoxes.Sort();
	const int BoxesNumber = SameCountryBoxes.Num();
	for (int i = 0; i < BoxesNumber - 1; ++i)
	{
		for (const auto& BoxProvince: SameCountryBoxes[i]->GetProvinces())
		{
			SameCountryBoxes[BoxesNumber - 1]->AddProvince(BoxProvince);
			ProvinceBox[BoxProvince] = SameCountryBoxes[BoxesNumber - 1];
		}
		delete SameCountryBoxes[i];
		Boxes.Remove(SameCountryBoxes[i]);
	}
	AddProvinceToBox(SameCountryBoxes[BoxesNumber - 1], Province);
	NotifyBoxUpdate(SameCountryBoxes[BoxesNumber - 1]);
	return true;
}

void UBoxesMap::CreateNewBox(UProvince* Province)
{
	FProvincesBox* Box = new FProvincesBox(this, Province->GetCountryController());
	Box->AddProvince(Province);
		
	ProvinceBox[Province] = Box;
	Boxes.Add(Box);

	NotifyBoxUpdate(Box);

}

void UBoxesMap::CalculateProvinceCorners()
{
	const UProvincesMap* ProvincesMap = GetWorld()->GetSubsystem<UProvincesMap>();
	for (const auto& Province: GetWorld()->GetSubsystem<UProvinceManager>()->GetAllProvinces())
	{
		
		FVector2d LeftTopCorner = FVector2d(INT_MAX, INT_MAX);
		FVector2d RightBottomCorner = FVector2d(0, 0);
		
		for (const auto& Index: ProvincesMap->GetProvincePositions(Province->GetId()))
		{
			const FVector2d Position = FTextureUtils::GetPositionVector(Index, SizeVector);
			LeftTopCorner.X = FMath::Min(LeftTopCorner.X, Position.X);
			LeftTopCorner.Y = FMath::Min(LeftTopCorner.Y, Position.Y);
			RightBottomCorner.X = FMath::Max(RightBottomCorner.X, Position.X);
			RightBottomCorner.Y = FMath::Max(RightBottomCorner.Y, Position.Y);
		}
		
		LeftTopCorners.Add(Province, LeftTopCorner);
		RightBottomCorners.Add(Province, RightBottomCorner);
		
	}
}

void UBoxesMap::CalculateBoxes()
{
	UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	const TMap<FColor, TSet<FColor>>& Neighbours = GetWorld()->GetSubsystem<UProvincesMap>()->GetNeighbours();
	for (const auto& [From, Tos]: Neighbours)
	{
		UProvince* Province = ProvinceManager->GetProvince(From);
		if (!Province || ProvinceBox.Contains(Province)) continue;
		FProvincesBox* Box = new FProvincesBox(this, Province->GetCountryController());
		AddProvincesToBox(Box, Province, Province->GetCountryController(), ProvinceManager);
		Boxes.Add(Box);
	}
}

void UBoxesMap::AddProvincesToBox(FProvincesBox* Box, UProvince* FromProvince, UCountry* Country, UProvinceManager* ProvinceManager)
{
	Box->AddProvince(FromProvince);
	ProvinceBox.Add(FromProvince, Box);
	for (const auto& To: GetWorld()->GetSubsystem<UProvincesMap>()->GetNeighbours()[FromProvince->GetId()])
	{
		UProvince* ToProvince = ProvinceManager->GetProvince(To);
		if (!ToProvince || ToProvince->GetCountryController() != Country || ProvinceBox.Contains(ToProvince)) continue;
		AddProvincesToBox(Box, ToProvince, Country, ProvinceManager);
	}
}
