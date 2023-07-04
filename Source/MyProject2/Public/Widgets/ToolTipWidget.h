// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"
#include "ToolTipWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UToolTipWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	URichTextBlock* TextBlock;

	UPROPERTY(EditAnywhere)
	FText Format;

	template <typename... ArgTypes>
	void SetData(ArgTypes... Args)
	{
		TextBlock->SetText(FText::Format(FTextFormat(Format), Args...));
	}
};
