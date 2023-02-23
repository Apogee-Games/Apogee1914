#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* Button;
	
	void Init(const FUnitDescription* ProvidedUnitDescription);
	
private:
	const FUnitDescription* UnitDescription;

	void SetUnitName(const FName& UnitName) const;
	
	UFUNCTION()
	void OnButtonClick();
};
