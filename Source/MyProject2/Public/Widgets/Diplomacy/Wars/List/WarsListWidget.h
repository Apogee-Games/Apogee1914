#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Diplomacy/Interfaces/Observers/WarDeclarationObserver.h"
#include "WarsListWidget.generated.h"

UCLASS()
class UWarsListWidget: public UUserWidget, public IWarDeclarationObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* WarsListView;

	virtual void NativeConstruct() override;
	
	virtual void WarWasDeclared(UWar* War) override;

	void RemoveWar(UWar* War);

	virtual void NativeDestruct() override;
};
