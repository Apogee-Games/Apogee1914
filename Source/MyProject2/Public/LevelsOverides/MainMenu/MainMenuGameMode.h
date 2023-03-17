#pragma once
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class AMainMenuGameMode: public AGameModeBase
{
	GENERATED_BODY()
public:
	AMainMenuGameMode();

	virtual void BeginPlay() override;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
