#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyProject2/Military/Instances/Units/Unit.h"
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

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	void Init();
	
	void AddUnit(UUnit* Unit);

	void RemoveUnit(UUnit* Unit);

	bool IsEmpty() const;
	
private:
	TArray<UUnit*> Units;

	UFUNCTION()
	void OnClicked();
	
	void UpdateCountText();
};
