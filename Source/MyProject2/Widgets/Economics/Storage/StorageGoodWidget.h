#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyProject2/Economics/Instances/Public/Storage.h"
#include "StorageGoodWidget.generated.h"

UCLASS()
class MYPROJECT2_API UStorageGoodWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* GoodNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CountryStorageCountTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LowerStrataStorageCountTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* MiddleStrataStorageCountTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UpperStrataStorageCountTextBlock;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetGood(UObject* ProvidedGood);
	
	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	TMap<EStorageType, UTextBlock*> TypeTextBlockMapping;

	UStoredGood* Good;
};

