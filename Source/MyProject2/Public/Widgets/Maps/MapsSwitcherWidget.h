#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/HorizontalBox.h"
#include "Maps/MapController.h"

#include "MapsSwitcherWidget.generated.h"

UCLASS()
class UMapsSwitcherWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TMap<EMapMode, UTexture2D*> MapModesIcons;
	
	UPROPERTY(EditAnywhere)
	TMap<EMapMode, FString> MapModesNames;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UHorizontalBox* MapOptions;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	UWidget* CreateContentWidget(FName Item);

	UFUNCTION()
	UWidget* CreateItemWidget(FName Item);
};
