#pragma once
#include "GameFramework/GameModeBase.h"
#include "CountrySelectionLevelGameMode.generated.h"

UCLASS()
class ACountrySelectionLevelGameMode: public AGameModeBase
{
	GENERATED_BODY()
public:
	ACountrySelectionLevelGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
