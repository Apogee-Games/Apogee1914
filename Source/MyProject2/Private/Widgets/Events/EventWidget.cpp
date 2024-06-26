
#include "Widgets/Events/EventWidget.h"

#include "Administration/Descriptions/Country/CountryDescription.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Canvas.h"
#include "Utils/TextureUtils.h"
#include "Widgets/Events/EventChoiceCarrier.h"

void UEventWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ButtonForMoving->OnPressed.AddDynamic(this, &UEventWidget::OnButtonForMovingPress);
	ButtonForMoving->OnReleased.AddDynamic(this, &UEventWidget::UEventWidget::OnButtonForMovingRelease);
}

void UEventWidget::Init(UEventDescription* EventDescription, UCountryDescription* CountryDescription, const TMap<FName, bool>& ChoicesConditionsEvaluated)
{
	TitleTextBlock->SetText(EventDescription->Title);
	TextTextBlock->SetText(EventDescription->Text);

	Image->SetBrushResourceObject(EventDescription->Image);

	for (const auto& Choice: EventDescription->Choices)
	{
		UEventChoiceCarrier* Carrier = NewObject<UEventChoiceCarrier>(this); // TODO: Do we need it :)
		Carrier->Init(Choice, CountryDescription, EventDescription, ChoicesConditionsEvaluated);
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
