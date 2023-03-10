#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/ListView.h"
#include "MyProject2/Events/EventDescription/EventDescription.h"
#include "EventWidget.generated.h"

class UEventChoiceButtonWidget;

/**
 * Event widget
 */
UCLASS()
class MYPROJECT2_API UEventWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCanvasPanel* WidgetCanvasPanel;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TitleTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* Image;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TextTextBlock;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* ButtonForMoving;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UListView* ChoicesListView;
	
	virtual void NativeConstruct() override;

	void Init(FEventDescription* EventDescription, const FName& CountryTag, const TMap<FName, bool>& ChoicesConditionsEvaluated);
	
	void Tick();
private:
	FVector2d CurrentMousePosition;

	bool IsWidgetBeingMoved = false;

	UFUNCTION()
	void OnButtonForMovingPress();

	UFUNCTION()
	void OnButtonForMovingRelease();
};
