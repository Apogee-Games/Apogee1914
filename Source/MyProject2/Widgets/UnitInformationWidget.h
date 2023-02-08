#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyProject2/Military/Instances/Unit.h"
#include "UnitInformationWidget.generated.h"

UCLASS()
class UUnitInformationWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* FlagImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CountTextBlock;

	void AddUnit(UUnit* Unit);

	void RemoveUnit(UUnit* Unit);

	bool IsEmpty() const;
	
private:
	UPROPERTY()
	TArray<UUnit*> Units;
	
	void UpdateCountText();
};
