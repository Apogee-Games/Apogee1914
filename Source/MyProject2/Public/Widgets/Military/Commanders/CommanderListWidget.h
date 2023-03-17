#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "People/Instances/Person.h"
#include "CommanderListWidget.generated.h"

UCLASS()
class UCommanderListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* CommandersListView;

	void AddCommander(UPerson* Commander);
};
