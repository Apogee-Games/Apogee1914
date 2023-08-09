#include "Maps/MapsDataGatherer.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Maps/ProvincesBox.h"
#include "Utils/TextureUtils.h"

void UMapsDataGatherer::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

FVector2d UMapsDataGatherer::GetSizeVector() const
{
	return SizeVector;
}

const FColor& UMapsDataGatherer::GetColor(int32 Position) const
{
	return PositionColor[Position];
}

const TArray<FColor>& UMapsDataGatherer::GetColors() const
{
	return PositionColor;
}

bool UMapsDataGatherer::HasProvincePosition(const FColor& Color) const
{
	return ColorPosition.Contains(Color);
}

const TArray<int32>& UMapsDataGatherer::GetProvincePositions(const FColor& Color) const
{
	if (!ColorPosition.Contains(Color))
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, Color.ToHex());
		}

		static TArray<int32> Array;
		return Array;
	}
	return ColorPosition[Color];
}

const TMap<FColor, TSet<FColor>>& UMapsDataGatherer::GetNeighbourColors() const
{
	return NeighbourColors;
}

const TMap<UProvince*, TSet<UProvince*>>& UMapsDataGatherer::GetNeighbourProvinces()
{
	return NeighbourProvinces;
}

const TArray<TSharedPtr<FProvincesBox>>& UMapsDataGatherer::GetBoxes() const
{
	return Boxes;
}

const FVector2d& UMapsDataGatherer::GetLeftTopCorner(UProvince* Province) const
{
	return LeftTopCorners[Province];
}

const FVector2d& UMapsDataGatherer::GetRightBottomCorner(UProvince* Province) const
{
	return RightBottomCorners[Province];
}

FVector2d UMapsDataGatherer::GetProvinceCenter(const FColor& Color)
{
	return ProvinceCenters[Color];
}

FVector2d UMapsDataGatherer::GetProvinceCenter(UProvince* Province)
{
	return ProvinceCenters[Province->GetId()];
}

/*
void UMapsDataGatherer::ProvinceHasNewControllingCountry(UProvince* Province)
{
	RemoveProvinceFromBox(Province);
	
	if (AddProvinceToNeighbourBoxes(Province)) return;

	CreateNewBox(Province);
}*/

ELoadStage UMapsDataGatherer::GetLoadStage()
{
	return ELoadStage::MapsDataGatherer;
}

void UMapsDataGatherer::CalculateMappers(UTexture2D* ProvinceMap)
{
	const FColor* Colors = FTextureUtils::GetPixels(ProvinceMap, LOCK_READ_WRITE);

	const UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	
	for (int32 i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		PositionColor[i] = FColor(Colors[i]);
		
		if (!ColorPosition.Contains(PositionColor[i])) {
			ColorPosition.Add(PositionColor[i], TArray<int32>());
			
			if (UProvince* Province = ProvinceManager->GetProvince(PositionColor[i]))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s is here"), *Province->GetName().ToString());
			} else
			{
				UE_LOG(LogTemp, Error, TEXT("%s is not here"), *PositionColor[i].ToString());
			}
		}
		
		ColorPosition[PositionColor[i]].Add(i);
	}

	FTextureUtils::UnlockPixels(ProvinceMap);
}

void UMapsDataGatherer::FindNeighbours()
{
	for (const auto& [Color, Positions]: ColorPosition)
	{
		NeighbourColors.Add(Color);	
	}

	int32 Width = static_cast<int>(SizeVector.X);
	int32 Height = static_cast<int>(SizeVector.Y);
	
	for (int32 i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		const int32 y = i / Width;
		const int32 x = i % Width;
		
		if (x > 0 && PositionColor[i] != PositionColor[i - 1])
		{
			NeighbourColors[PositionColor[i]].Add(PositionColor[i - 1]);
			NeighbourColors[PositionColor[i - 1]].Add(PositionColor[i]);
		}
		if (x + 1 < SizeVector.X && PositionColor[i] != PositionColor[i + 1])
		{
			NeighbourColors[PositionColor[i]].Add(PositionColor[i + 1]);
			NeighbourColors[PositionColor[i + 1]].Add(PositionColor[i]);
		}
		if (y > 0 && PositionColor[i] != PositionColor[i - Width])
		{
			NeighbourColors[PositionColor[i]].Add(PositionColor[i - Width]);
			NeighbourColors[PositionColor[i - Width]].Add(PositionColor[i]);
		}
		if (y + 1 < Height && PositionColor[i] != PositionColor[i + Width])
		{
			NeighbourColors[PositionColor[i]].Add(PositionColor[i + Width]);
			NeighbourColors[PositionColor[i + Width]].Add(PositionColor[i]);
		}
	}

	// TODO: Think of uniting this two types
	
	UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();

	for (const auto& [Color, DirectNeighboursColors]: NeighbourColors)
	{
		UProvince* Province = ProvinceManager->GetProvince(Color);
		if (!Province) continue;;

		TSet<UProvince*> ProvinceDirectNeighbours;
		for (const auto& ColorB: DirectNeighboursColors)
		{
			UProvince* ProvinceB = ProvinceManager->GetProvince(ColorB);
			if (!ProvinceB) continue;

			ProvinceDirectNeighbours.Add(ProvinceB);
		}
		NeighbourProvinces.Add(Province, ProvinceDirectNeighbours);
	}
}

void UMapsDataGatherer::Clear()
{
	ProvincesMapTexture = nullptr;
	ColorPosition.Empty();
	NeighbourColors.Empty();
	PositionColor.Empty();
	
	Boxes.Empty();
	LeftTopCorners.Empty();
	RightBottomCorners.Empty();
	
	ProvinceCenters.Empty();
}


void UMapsDataGatherer::Init(UScenario* Scenario)
{
	ProvincesMapTexture = Scenario->ProvincesMapTexture;
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);

	PositionColor.SetNum(SizeVector.X * SizeVector.Y);
	
	CalculateMappers(ProvincesMapTexture);
	FindNeighbours();

	CalculateProvinceCorners();
	CalculateBoxes();

	CalculateCentersForAllProvinces();
	
	//GetGameInstance()->GetSubsystem<UProvinceManager>()->AddProvinceControllingCountryObserver(this);
	// TODO: think of order (meaning new controller -> update distances or new owner update distances)
}


void UMapsDataGatherer::CalculateProvinceCorners()
{
	for (const auto& Province: GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces())
	{
		
		FVector2d LeftTopCorner = FVector2d(INT_MAX, INT_MAX);
		FVector2d RightBottomCorner = FVector2d(0, 0);
		
		for (const auto& Index: ColorPosition[Province->GetId()])
		{
			const FVector2d Position = FTextureUtils::GetPositionVector(Index, SizeVector);
			LeftTopCorner.X = FMath::Min(LeftTopCorner.X, Position.X);
			LeftTopCorner.Y = FMath::Min(LeftTopCorner.Y, Position.Y);
			RightBottomCorner.X = FMath::Max(RightBottomCorner.X, Position.X + 1.0);
			RightBottomCorner.Y = FMath::Max(RightBottomCorner.Y, Position.Y + 1.0);
		}
		
		LeftTopCorners.Add(Province, LeftTopCorner);
		RightBottomCorners.Add(Province, RightBottomCorner);
	}
}


void UMapsDataGatherer::CalculateBoxes()
{
	UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	for (const auto& [From, Tos]: NeighbourColors)
	{
		UProvince* Province = ProvinceManager->GetProvince(From);
		if (!Province || ProvinceBox.Contains(Province)) continue;
		TSharedPtr<FProvincesBox> Box = MakeShared<FProvincesBox>(this, Province->GetCountryController());
		AddProvincesToBox(Box, Province, Province->GetCountryController(), ProvinceManager);
		Boxes.Add(Box);
	}
}

void UMapsDataGatherer::AddProvincesToBox(TSharedPtr<FProvincesBox> Box, UProvince* FromProvince, UCountry* Country, UProvinceManager* ProvinceManager)
{
	Box->AddProvince(FromProvince);
	ProvinceBox.Add(FromProvince, Box);
	for (const auto& To: NeighbourColors[FromProvince->GetId()])
	{
		UProvince* ToProvince = ProvinceManager->GetProvince(To);
		if (!ToProvince || ToProvince->GetCountryController() != Country || ProvinceBox.Contains(ToProvince)) continue;
		AddProvincesToBox(Box, ToProvince, Country, ProvinceManager);
	}
}

bool UMapsDataGatherer::AddProvinceToBox(TSharedPtr<FProvincesBox> Box, UProvince* Province)
{
	Box->AddProvince(Province);
	ProvinceBox[Province] = Box;
	return true;	
}

bool UMapsDataGatherer::MergeBoxesAndAddProvince(TArray<TSharedPtr<FProvincesBox>>& SameCountryBoxes, UProvince* Province)
{
	SameCountryBoxes.Sort(FProvincesBox::CompareAscending);
	const int32 BoxesNumber = SameCountryBoxes.Num();
	for (int32 i = 0; i < BoxesNumber - 1; ++i)
	{
		for (const auto& BoxProvince: SameCountryBoxes[i]->GetProvinces())
		{
			SameCountryBoxes[BoxesNumber - 1]->AddProvince(BoxProvince);
			ProvinceBox[BoxProvince] = SameCountryBoxes[BoxesNumber - 1];
		}
		Boxes.Remove(SameCountryBoxes[i]);
	}
	AddProvinceToBox(SameCountryBoxes[BoxesNumber - 1], Province);
	return true;
}

void UMapsDataGatherer::CreateNewBox(UProvince* Province)
{
	TSharedPtr<FProvincesBox> Box = MakeShared<FProvincesBox>(this, Province->GetCountryController());
	Box->AddProvince(Province);
		
	ProvinceBox[Province] = Box;
	Boxes.Add(Box);
}


void UMapsDataGatherer::RemoveProvinceFromBox(UProvince* Province)
{
	ProvinceBox[Province]->RemoveProvince(Province);
	if (ProvinceBox[Province]->GetProvinces().IsEmpty())
	{
		Boxes.Remove(ProvinceBox[Province]);
	}
}

bool UMapsDataGatherer::AddProvinceToNeighbourBoxes(UProvince* Province)
{
	const UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	const TSet<FColor>& Neighbours = NeighbourColors[Province->GetId()];

	TArray<TSharedPtr<FProvincesBox>> SameCountryBoxes;

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

void UMapsDataGatherer::CalculateCentersForAllProvinces()
{
	for (const auto& Province : GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces())
	{
		CalculateProvinceCenter(Province->GetId());
	}
}

FVector2d UMapsDataGatherer::CalculateProvinceCenter(const FColor& Color)
{
	ProvinceCenters.Add(Color, {0, 0});
	
	for (const auto& Position : ColorPosition[Color])
	{
		ProvinceCenters[Color] += FTextureUtils::GetPositionVector(Position, SizeVector);
	}

	const FVector2d Result = ProvinceCenters[Color] / ColorPosition[Color].Num() / SizeVector;
	
	ProvinceCenters[Color] = Result;

	return Result;
}

