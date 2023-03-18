#pragma once
#include "Widgets/MainMenu/MainMenuWidget.h"
#include "MainMenuPawn.generated.h"

UCLASS()
class AMainMenuPawn: public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY()
	UMainMenuWidget* MainMenuWidget;
};
