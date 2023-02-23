#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyProject2/Military/Descriptions/UnitDescription.h"
#include "UnitTypeDescriptionWidget.generated.h"

UCLASS()
class UUnitTypeDescriptionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* UnitNameTextBlock;

	void Init(const FUnitDescription* UnitDescription);
	
	void SetUnitName(const FName& UnitName);
};
