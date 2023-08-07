#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Diplomacy/Instances/War.h"
#include "WarDescriptionWidget.generated.h"

UCLASS()
class UWarDescriptionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* WarNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* DefendersListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* AttackersListView;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UFUNCTION()
	void OnWarSelected(UWar* War);
};
