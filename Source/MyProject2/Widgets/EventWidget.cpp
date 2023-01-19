#include "EventWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Canvas.h"
#include "MyProject2/TextureUtils.h"
#include "EventChoiceButtonWidget.h"

void UEventWidget::SetTitle(const FString& Title) const
{
	TitleTextBlock->SetText(FText::FromString(Title));
}

void UEventWidget::SetImage(const FString& ImagePath) const
{
	UTexture2D* ImageTexture = FTextureUtils::LoadTexture(ImagePath);

	Image->SetBrushResourceObject(ImageTexture);
}

void UEventWidget::SetText(const FString& Text) const
{
	TextTextBlock->SetText(FText::FromString(Text));
}

void UEventWidget::AddChoice(const FString& EventName, const FString& ChoiceName, const FString& CountryTag, const FString& ChoiceText, FEventManager* EventManager)
{
	UEventChoiceButtonWidget* ChoiceButtonWidget = CreateWidget<UEventChoiceButtonWidget>(GetWorld(), ChoiceButtonWidgetClass);
	ChoiceButtonWidget->Init(EventName, ChoiceName, CountryTag, ChoiceText, EventManager);
	
	ChoicesGridPanel->AddChildToGrid(ChoiceButtonWidget, CurrentChoice, 0);
	CurrentChoice++;

	UpdateSizes(ChoiceButtonWidget);
}

void UEventWidget::Tick()
{
	if (IsWidgetBeingMoved)
	{
		const FVector2d NewCurrentMousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

		if (CurrentMousePosition != NewCurrentMousePosition)
		{
			UCanvasPanelSlot* WidgetCanvasSlot = Cast<UCanvasPanelSlot>(WidgetCanvas->Slot);

			const FVector2d NewWidgetPosition = WidgetCanvasSlot->GetPosition() + NewCurrentMousePosition - CurrentMousePosition;

			WidgetCanvasSlot->SetPosition(NewWidgetPosition);

			CurrentMousePosition = NewCurrentMousePosition;
		}
	}
}

void UEventWidget::Init()
{
	ButtonForMoving->OnPressed.AddDynamic(this, &UEventWidget::OnButtonForMovingPress);
	ButtonForMoving->OnReleased.AddDynamic(this, &UEventWidget::UEventWidget::OnButtonForMovingRelease);
}

void UEventWidget::Init(const FString& Title, const FString& Text, const FString& ImagePath)
{
	Init();
	SetTitle(Title);
	SetText(Text);
	SetImage(ImagePath);
}

void UEventWidget::OnButtonForMovingPress()
{
	CurrentMousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	IsWidgetBeingMoved = true;
}

void UEventWidget::OnButtonForMovingRelease()
{
	IsWidgetBeingMoved = false;
}

void UEventWidget::UpdateSizes(const UEventChoiceButtonWidget* NewChoiceButton) const
{
	const FVector2d Margin = FVector2d(0, Cast<UCanvasPanelSlot>(NewChoiceButton->ChoiceButton->Slot)->GetPosition().Y);
	const FVector2d ButtonSize = FVector2d(0, Cast<UCanvasPanelSlot>(NewChoiceButton->ChoiceButton->Slot)->GetSize().Y);
	const FVector2d NewSize = Cast<UCanvasPanelSlot>(WidgetCanvas->Slot)->GetSize() + ButtonSize + Margin;
	
	Cast<UCanvasPanelSlot>(BackgroundImage->Slot)->SetSize(NewSize);
	Cast<UCanvasPanelSlot>(ButtonForMoving->Slot)->SetSize(NewSize);
	Cast<UCanvasPanelSlot>(WidgetCanvas->Slot)->SetSize(NewSize);
}
