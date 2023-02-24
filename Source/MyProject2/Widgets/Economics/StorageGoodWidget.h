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

	void Init(const FName& GoodName);

	void GoodIsUpdated(EStorageType StorageType, int NewAmount);

private:
	UPROPERTY()
	TMap<EStorageType, UTextBlock*> TypeTextBlockMapping;
};

