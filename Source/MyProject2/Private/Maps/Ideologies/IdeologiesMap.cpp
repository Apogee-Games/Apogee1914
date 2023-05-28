#include "Maps/Ideologies/IdeologiesMap.h"

#include "Administration/Instances/Country.h"
#include "Administration/Instances/Province.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Maps/Ideologies/IdeologiesMapUpdater.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Utils/TextureUtils.h"

void UIdeologiesMap::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UIdeologiesMap::UpdateMap()
{
	const TArray<UProvince*> Provinces = GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces();

	UProvincesMap* ProvincesMap = GetGameInstance()->GetSubsystem<UProvincesMap>();

	FColor* Colors = FTextureUtils::GetPixels(IdeologiesMapTexture, LOCK_READ_WRITE);

	TArray<FRunnableThread*> Threads;

	for (const auto& Province: Provinces)
	{
		FRunnableThread* Thread = UpdateProvince(
				ProvincesMap->GetProvincePositions(Province->GetId()),
				Colors,
				Province->GetCountryController()->GetIdeology()->Color,
				ToCStr(Province->GetName().ToString())
		);
		Threads.Add(Thread);
	}

	for (const auto& Thread: Threads)
	{
		Thread->WaitForCompletion();
	}

	FTextureUtils::UnlockPixels(IdeologiesMapTexture);
	IdeologiesMapTexture->UpdateResource();
}

void UIdeologiesMap::Clear()
{
	IdeologiesMapTexture = nullptr;
}

void UIdeologiesMap::Init(UScenario* Scenario)
{
	IdeologiesMapTexture = Scenario->IdeologiesMapTexture;
	UpdateMap();
}

FRunnableThread* UIdeologiesMap::UpdateProvince(const TArray<int32>& Position, FColor* Colors, FColor Color, const TCHAR* Name)
{
	FIdeologiesMapUpdater* Update = new FIdeologiesMapUpdater(Position, Colors, Color);
	return FRunnableThread::Create(Update, Name);
}
