#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyProject2/Military/Instances/Units/Unit.h"

#include "UnitSupplyWidget.generated.h"

UCLASS()
class UUnitSupplyWidget: public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UnitNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UnitNeedsTextBlock;
	
	void Init(FUnit* Unit);
	
	void UnitWasSupplied(FUnit* Unit);
};
