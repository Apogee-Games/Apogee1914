#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "WarsListWidget.generated.h"

UCLASS()
class UWarsListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* WarsListView;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UFUNCTION()
	void OnWarStatusChanged(UWar* War, EWarStatus WarStatus);
};
