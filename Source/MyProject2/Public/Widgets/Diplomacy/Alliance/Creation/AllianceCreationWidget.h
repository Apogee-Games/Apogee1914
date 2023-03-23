#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ListView.h"

#include "AllianceCreationWidget.generated.h"

UCLASS()
class UAllianceCreationWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UEditableTextBox* AllianceNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* InvitationalCountriesListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* ToBeInvitedCountriesListView;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CreateAllianceButton;

	void Init();

	virtual void NativeConstruct() override;

	void SetCountry(UCountry* Country);

	void AddToBeInvitedCountry(UCountry* Country);

	void RemoveToBeInvitedCountry(UCountry* Country);

private:
	UFUNCTION()
	void OnCreateAllianceButtonClick();
};
