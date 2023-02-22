#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
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
	UTextBlock* TitleTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* Image;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* BackgroundImage;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TextTextBlock;

	/* Invisible button which is rendered on top of whole widget (except choices button) to allow tracing of movement*/
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* ButtonForMoving;

	/* Canvas that has all widget elements in it used to allow moving of whole widget */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCanvasPanel* WidgetCanvas;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UGridPanel* ChoicesGridPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEventChoiceButtonWidget> ChoiceButtonWidgetClass;

	/*
	 * Method used to set event title 
	 */
	void SetTitle(const FText& Title) const;
	
	/*
	 * Method used to set event image 
	 */
	void SetImage(const FName& ImagePath) const;
	
	/*
	 * Method used to set event text 
	 */
	void SetText(const FText& Text) const;
	
	/*
	 * Method used to add event choice
	 * Updates background sizes, so that choices button won't be outside of the event them 
	 */
	void AddChoice(const FName& EventName, const FName& ChoiceName, const FName& CountryTag, const FText& ChoiceText);

	/**
	 * Method used for tracking per frame actions, such as moving
	 */
	void Tick();

	/**
	 * Adds button action bindings
	 */
	void Init();
	
	/**
	 * Adds button action bindings and sets some event data
	 */
	void Init(const FText& Title, const FText& Text, const FName& ImagePath);
	
private:
	int CurrentChoice = 0;
	
	FVector2d CurrentMousePosition;

	bool IsWidgetBeingMoved = false;

	UFUNCTION()
	void OnButtonForMovingPress();

	UFUNCTION()
	void OnButtonForMovingRelease();

	void UpdateSizes(const UEventChoiceButtonWidget* NewChoiceButton) const;
};
