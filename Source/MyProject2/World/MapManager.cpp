// #include "MapManager.h"
//
//
// FMapManager::FMapManager(const FString& ProvincesMapTexturePath, const FString& BlankMapTexturePath,
//                          const FString& CountriesColorsMapTexturePath, const FString& OutlinesMapTexturePath):
// 	GameState(nullptr)
// {
// 	ProvincesMapTexture = LoadTexture(ProvincesMapTexturePath);
// 	BlankMapTexture = LoadTexture(BlankMapTexturePath);
// 	CountriesColorsMapTexture = LoadTexture(CountriesColorsMapTexturePath);
// 	OutlinesMapTexture = LoadTexture(OutlinesMapTexturePath);
// 	SizeVector = GetTextureSizeVector(ProvincesMapTexture);
// 	CentersMapTexture = LoadTexture("/Game/maps/Centers");
// }
//
// void FMapManager::SetGameState(const AMyGameState* NewGameState)
// {
// 	GameState = NewGameState;
// }
//
//
//
//
// void FMapManager::Select(const FColor& Color)
// {
// 	
// }
//
// void FMapManager::BeginPlay()
// {
// 	UpdateCountriesMapColors();
//
// 	CreateOutline();
// }
//
// void FMapManager::DisplayCenters()
// {
// 	FColor* Colors = GetPixels(CentersMapTexture, LOCK_READ_WRITE);
//
// 	for (const auto Pair : ProvincesCenters)
// 	{
// 		Colors[Pair.Value - 2] = FColor(255, 0, 0);
// 		Colors[Pair.Value - 1] = FColor(255, 0, 0);
// 		Colors[Pair.Value] = FColor(255, 0, 0);
// 		Colors[Pair.Value + 1] = FColor(255, 0, 0);
// 		Colors[Pair.Value + 2] = FColor(255, 0, 0);
// 	}
//
// 	UnlockPixels(CentersMapTexture);
//
// 	CentersMapTexture->UpdateResource();
// }
//
//
// int FMapManager::GetMapSize() const
// {
// 	return SizeVector.X * SizeVector.Y;
// }
//
