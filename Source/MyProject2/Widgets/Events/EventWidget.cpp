#include "EventWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Canvas.h"
#include "MyProject2/Utils/TextureUtils.h"
#include "EventChoiceButtonWidget.h"
#include "EventChoiceCarrier.h"

void UEventWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ButtonForMoving->OnPressed.AddDynamic(this, &UEventWidget::OnButtonForMovingPress);
	ButtonForMoving->OnReleased.AddDynamic(this, &UEventWidget::UEventWidget::OnButtonForMovingRelease);
}

void UEventWidget::Init(FEventDescription* EventDescription, const FName& CountryTag, const TMap<FName, bool>& ChoicesConditionsEvaluated)
{
	TitleTextBlock->SetText(EventDescription->Title);
	TextTextBlock->SetText(EventDescription->Text);

	UTexture2D* ImageTexture = FTextureUtils::LoadTexture(EventDescription->ImagePath.ToString());
	Image->SetBrushResourceObject(ImageTexture);

	for (const auto& Choice: EventDescription->Choices)
	{
		UEventChoiceCarrier* Carrier = NewObject<UEventChoiceCarrier>();
		Carrier->Init(Choice, CountryTag, EventDescription, ChoicesConditionsEvaluated);
		ChoicesListView->AddItem(Carrier);
	}
}

void UEventWidget::Tick()
{
	if (IsWidgetBeingMoved)
	{
		const FVector2d NewCurrentMousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

		if (CurrentMousePosition != NewCurrentMousePosition)
		{
			UCanvasPanelSlot* WidgetCanvasSlot = Cast<UCanvasPanelSlot>(WidgetCanvasPanel->Slot);

			const FVector2d NewWidgetPosition = WidgetCanvasSlot->GetPosition() + NewCurrentMousePosition - CurrentMousePosition;

			WidgetCanvasSlot->SetPosition(NewWidgetPosition);

			CurrentMousePosition = NewCurrentMousePosition;
		}
	}
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
