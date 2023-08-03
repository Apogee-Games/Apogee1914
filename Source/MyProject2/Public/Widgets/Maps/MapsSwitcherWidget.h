#pragma once
#include "Blueprint/UserWidget.h"
#include "Maps/MapController.h"
#include "MapsSwitcherWidget.generated.h"

class UMapModeItemWidget;
class UMapModeComboBox;

UCLASS()
class UMapsSwitcherWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UHorizontalBox* MapOptions;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMapModeComboBox> MapModeComboBoxClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMapModeItemWidget> MapModeItemWidgetClass;

	virtual void NativeConstruct() override;
protected:
	void RefreshOptions(const TArray<EMapMode>& MapItems);

	UFUNCTION()
	UWidget* OnCreateContentWidget(EMapMode Item);

	UFUNCTION()
	UWidget* OnCreateItemWidget(EMapMode Item);

	UFUNCTION()
	void OnItemSelected(EMapMode SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnMapModeSelected(EMapMode MapMode);

	void CreateWidgets();
	void CreateComboBoxes(const TArray<EMapMode>& MapItems);

	UPROPERTY()
	UMapModeItemWidget* NoneMapModeContentWidget;
	
	UPROPERTY()
	TArray<UMapModeComboBox*> ComboBoxes; 
	
	UPROPERTY()
	TMap<EMapMode, UMapModeItemWidget*> Widgets;
	
	UPROPERTY()
	UMapController* MapController;
};
