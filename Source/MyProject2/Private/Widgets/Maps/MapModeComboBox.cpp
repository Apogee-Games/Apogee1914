#include "Widgets/Maps/MapModeComboBox.h"

#define LOCTEXT_NAMESPACE "MapModeComboBox"

/////////////////////////////////////////////////////
// UMapModeComboBox

FReply SMapModeComboRow::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		TSharedPtr< ITypedTableView<TSharedPtr<EMapMode>> > OwnerWidget = this->OwnerTablePtr.Pin();

		const TSharedPtr<EMapMode>* MyItem = OwnerWidget->Private_ItemFromWidget( this );
		const bool bIsSelected = OwnerWidget->Private_IsItemSelected( *MyItem );
				
		if (bIsSelected)
		{
			// Reselect content to ensure selection is taken
			OwnerWidget->Private_SignalSelectionChanged(ESelectInfo::Direct);
			return FReply::Handled();
		}
	}
	return STableRow<TSharedPtr<EMapMode>>::OnMouseButtonDown(MyGeometry, MouseEvent);
}

SMapModeComboBox::FArguments::FArguments(): _Content()
                                            , _ComboBoxStyle(&FAppStyle::Get().GetWidgetStyle< FComboBoxStyle >("ComboBox"))
                                            , _ButtonStyle(nullptr)
                                            , _ItemStyle(&FAppStyle::Get().GetWidgetStyle< FTableRowStyle >("ComboBox.Row"))
                                            , _ScrollBarStyle(&FAppStyle::Get().GetWidgetStyle<FScrollBarStyle>("ScrollBar"))
                                            , _ContentPadding(_ComboBoxStyle->ContentPadding)
                                            , _ForegroundColor(FSlateColor::UseStyle())
                                            , _OptionsSource()
                                            , _OnSelectionChanged()
                                            , _OnGenerateWidget()
                                            , _InitiallySelectedItem(MakeShared<EMapMode>())
                                            , _Method()
                                            , _MaxListHeight(450.0f)
                                            , _HasDownArrow( true )
                                            , _EnableGamepadNavigationMode(false)
                                            , _IsFocusable( true )
{}

void SMapModeComboBox::Construct(const FArguments& InArgs)
{
	check(InArgs._ComboBoxStyle);

	ItemStyle = InArgs._ItemStyle;
	ComboBoxStyle = InArgs._ComboBoxStyle;
	MenuRowPadding = ComboBoxStyle->MenuRowPadding;

	// Work out which values we should use based on whether we were given an override, or should use the style's version
	const FComboButtonStyle& OurComboButtonStyle = ComboBoxStyle->ComboButtonStyle;
	const FButtonStyle* const OurButtonStyle = InArgs._ButtonStyle ? InArgs._ButtonStyle : &OurComboButtonStyle.ButtonStyle;
	PressedSound = InArgs._PressedSoundOverride.Get(ComboBoxStyle->PressedSlateSound);
	SelectionChangeSound = InArgs._SelectionChangeSoundOverride.Get(ComboBoxStyle->SelectionChangeSlateSound);

	this->OnComboBoxOpening = InArgs._OnComboBoxOpening;
	this->OnSelectionChanged = InArgs._OnSelectionChanged;
	this->OnGenerateWidget = InArgs._OnGenerateWidget;
	this->OnLeftMouseClick = InArgs._OnLeftMouseClick;
	this->EnableGamepadNavigationMode = InArgs._EnableGamepadNavigationMode;
	this->bControllerInputCaptured = false;

	OptionsSource = InArgs._OptionsSource;
	CustomScrollbar = InArgs._CustomScrollbar;

	ComboBoxMenuContent =
		SNew(SBox)
		.MaxDesiredHeight(InArgs._MaxListHeight)
		[
			SAssignNew(this->ComboListView, SListView<TSharedPtr<EMapMode>>)
				.ListItemsSource(InArgs._OptionsSource)
				.OnGenerateRow(this, &SMapModeComboBox::GenerateMenuItemRow)
				.OnSelectionChanged(this, &SMapModeComboBox::OnSelectionChanged_Internal)
				.OnKeyDownHandler(this, &SMapModeComboBox::OnKeyDownHandler)
				.SelectionMode(ESelectionMode::Single)
				.ScrollBarStyle(InArgs._ScrollBarStyle)
				.ExternalScrollbar(InArgs._CustomScrollbar)
				
		];

	// Set up content
	TSharedPtr<SWidget> ButtonContent = InArgs._Content.Widget;
	if (InArgs._Content.Widget == SNullWidget::NullWidget)
	{
		SAssignNew(ButtonContent, STextBlock)
			.Text(NSLOCTEXT("SComboBox", "ContentWarning", "No Content Provided"))
			.ColorAndOpacity( FLinearColor::Red);
	}


	SComboButton::Construct( SComboButton::FArguments()
	                         .ComboButtonStyle(&OurComboButtonStyle)
	                         .ButtonStyle(OurButtonStyle)
	                         .Method( InArgs._Method )
	                         .ButtonContent()
	                         [
		                         ButtonContent.ToSharedRef()
	                         ]
	                         .MenuContent()
	                         [
		                         ComboBoxMenuContent.ToSharedRef()
	                         ]
	                         .HasDownArrow( InArgs._HasDownArrow )
	                         .ContentPadding( InArgs._ContentPadding )
	                         .ForegroundColor( InArgs._ForegroundColor )
	                         .OnMenuOpenChanged(this, &SMapModeComboBox::OnMenuOpenChanged)
	                         .IsFocusable(InArgs._IsFocusable)
	                         .CollapseMenuOnParentFocus(InArgs._CollapseMenuOnParentFocus)
	);
	SetMenuContentWidgetToFocus(ComboListView);

	// Need to establish the selected item at point of construction so its available for querying
	// NB: If you need a selection to fire use SetItemSelection rather than setting an IntiallySelectedItem
	SelectedItem = InArgs._InitiallySelectedItem;
	ComboListView->Private_SetItemSelection(SelectedItem, true);
	ComboListView->RequestScrollIntoView(SelectedItem, 0);
		
}

SMapModeComboBox::SMapModeComboBox()
{
#if WITH_ACCESSIBILITY
	AccessibleBehavior = EAccessibleBehavior::Auto;
	bCanChildrenBeAccessible = true;
#endif
}

SMapModeComboBox::FSlateAccessibleComboBox::FSlateAccessibleComboBox(TWeakPtr<SWidget> InWidget): FSlateAccessibleWidget(InWidget, EAccessibleWidgetType::ComboBox)
{}

IAccessibleProperty* SMapModeComboBox::FSlateAccessibleComboBox::AsProperty()
{ 
	return this; 
}

FString SMapModeComboBox::FSlateAccessibleComboBox::GetValue() const
{
	if (Widget.IsValid())
	{
		TSharedPtr<SMapModeComboBox> ComboBox = StaticCastSharedPtr<SMapModeComboBox>(Widget.Pin());
		TSharedPtr<ITableRow> SelectedTableRow = ComboBox->ComboListView->WidgetFromItem(ComboBox->SelectedItem);
		if (SelectedTableRow.IsValid())
		{
			TSharedRef<SWidget> TableRowWidget = SelectedTableRow->AsWidget();
			return TableRowWidget->GetAccessibleText().ToString();
		}
	}
	return FText::GetEmpty().ToString();
}

FVariant SMapModeComboBox::FSlateAccessibleComboBox::GetValueAsVariant() const
{
	return FVariant(GetValue());
}

TSharedRef<FSlateAccessibleWidget> SMapModeComboBox::CreateAccessibleWidget()
{
	return MakeShareable<FSlateAccessibleWidget>(new SMapModeComboBox::FSlateAccessibleComboBox(SharedThis(this)));
}

TOptional<FText> SMapModeComboBox::GetDefaultAccessibleText(EAccessibleType AccessibleType) const
{
	// current behaviour will red out the  templated type of the combo box which is verbose and unhelpful 
	// This coupled with UIA type will announce Combo Box twice, but it's the best we can do for now if there's no label
	//@TODOAccessibility: Give a better name
	static FString Name(TEXT("Combo Box"));
	return FText::FromString(Name);
}

void SMapModeComboBox::ClearSelection()
{
	ComboListView->ClearSelection();
}

void SMapModeComboBox::SetSelectedItem(TSharedPtr<EMapMode> InSelectedItem)
{
	ComboListView->SetSelection(InSelectedItem);
}

void SMapModeComboBox::SetEnableGamepadNavigationMode(bool InEnableGamepadNavigationMode)
{
	this->EnableGamepadNavigationMode = InEnableGamepadNavigationMode;
}

void SMapModeComboBox::SetMaxHeight(float InMaxHeight)
{
	ComboBoxMenuContent->SetMaxDesiredHeight(InMaxHeight);
}

void SMapModeComboBox::SetStyle(const FComboBoxStyle* InStyle)
{ 
	if (ComboBoxStyle != InStyle)
	{
		ComboBoxStyle = InStyle;
		InvalidateStyle();
	}
}

void SMapModeComboBox::InvalidateStyle()
{ 
	Invalidate(EInvalidateWidgetReason::Layout); 
}

void SMapModeComboBox::SetItemStyle(const FTableRowStyle* InItemStyle)
{ 
	if (ItemStyle != InItemStyle)
	{
		ItemStyle = InItemStyle;
		InvalidateItemStyle();
	}
}

void SMapModeComboBox::InvalidateItemStyle()
{ 
	Invalidate(EInvalidateWidgetReason::Layout); 
}

TSharedPtr<EMapMode> SMapModeComboBox::GetSelectedItem()
{
	return SelectedItem;
}

void SMapModeComboBox::RefreshOptions()
{
	ComboListView->RequestListRefresh();
}

FReply SMapModeComboBox::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (IsInteractable())
	{
		const EUINavigationAction NavAction = FSlateApplication::Get().GetNavigationActionFromKey(InKeyEvent);
		const EUINavigation NavDirection = FSlateApplication::Get().GetNavigationDirectionFromKey(InKeyEvent);
		if (EnableGamepadNavigationMode)
		{
			// The controller's bottom face button must be pressed once to begin manipulating the combobox's value.
			// Navigation away from the widget is prevented until the button has been pressed again or focus is lost.
			if (NavAction == EUINavigationAction::Accept)
			{
				if (bControllerInputCaptured == false)
				{
					// Begin capturing controller input and open the ListView
					bControllerInputCaptured = true;
					PlayPressedSound();
					OnComboBoxOpening.ExecuteIfBound();
					return SComboButton::OnButtonClicked();
				}
				else
				{
					// Set selection to the selected item on the list and close
					bControllerInputCaptured = false;

					// Re-select first selected item, just in case it was selected by navigation previously
					TArray<TSharedPtr<EMapMode>> SelectedItems = ComboListView->GetSelectedItems();
					if (SelectedItems.Num() > 0)
					{
						OnSelectionChanged_Internal(SelectedItems[0], ESelectInfo::Direct);
					}

					// Set focus back to ComboBox
					FReply Reply = FReply::Handled();
					Reply.SetUserFocus(this->AsShared(), EFocusCause::SetDirectly);
					return Reply;
				}

			}
			else if (NavAction == EUINavigationAction::Back || InKeyEvent.GetKey() == EKeys::BackSpace)
			{
				const bool bWasInputCaptured = bControllerInputCaptured;

				OnMenuOpenChanged(false);
				if (bWasInputCaptured)
				{
					return FReply::Handled();
				}
			}
			else
			{
				if (bControllerInputCaptured)
				{
					return FReply::Handled();
				}
			}
		}
		else
		{
			if (NavDirection == EUINavigation::Up)
			{
				const int32 SelectionIndex = OptionsSource->Find(GetSelectedItem());
				if (SelectionIndex >= 1)
				{
					// Select an item on the prev row
					SetSelectedItem((*OptionsSource)[SelectionIndex - 1]);
				}

				return FReply::Handled();
			}
			else if (NavDirection == EUINavigation::Down)
			{
				const int32 SelectionIndex = OptionsSource->Find(GetSelectedItem());
				if (SelectionIndex < OptionsSource->Num() - 1)
				{
					// Select an item on the next row
					SetSelectedItem((*OptionsSource)[SelectionIndex + 1]);
				}
				return FReply::Handled();
			}

			return SComboButton::OnKeyDown(MyGeometry, InKeyEvent);
		}
	}
	return SWidget::OnKeyDown(MyGeometry, InKeyEvent);
}

bool SMapModeComboBox::SupportsKeyboardFocus() const
{
	return bIsFocusable;
}

bool SMapModeComboBox::IsInteractable() const
{
	return IsEnabled();
}

FReply SMapModeComboBox::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		return SMapModeComboBox::OnButtonRightClick();
	}
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return SMapModeComboBox::OnButtonClicked();
	}

	return FReply::Unhandled();
}

TSharedRef<ITableRow> SMapModeComboBox::GenerateMenuItemRow(TSharedPtr<EMapMode> InItem,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	if (OnGenerateWidget.IsBound())
	{
		return SNew(SMapModeComboRow, OwnerTable)
				.Style(ItemStyle)
				.Padding(MenuRowPadding)
		[
			OnGenerateWidget.Execute(InItem)
		];
	}
	else
	{
		return SNew(SMapModeComboRow, OwnerTable)
		[
			SNew(STextBlock).Text(NSLOCTEXT("SlateCore", "ComboBoxMissingOnGenerateWidgetMethod", "Please provide a .OnGenerateWidget() handler."))
		];

	}
}

void SMapModeComboBox::OnMenuOpenChanged(bool bOpen)
{
	if (bOpen == false)
	{
		bControllerInputCaptured = false;

		// Ensure the ListView selection is set back to the last committed selection
		ComboListView->SetSelection(SelectedItem, ESelectInfo::OnNavigation);
		ComboListView->RequestScrollIntoView(SelectedItem, 0);

		// Set focus back to ComboBox for users focusing the ListView that just closed
		FSlateApplication::Get().ForEachUser([this](FSlateUser& User) 
		{
			TSharedRef<SWidget> ThisRef = this->AsShared();
			if (User.IsWidgetInFocusPath(this->ComboListView))
			{
				User.SetFocus(ThisRef);
			}
		});

	}
}

void SMapModeComboBox::OnSelectionChanged_Internal(TSharedPtr<EMapMode> ProposedSelection, ESelectInfo::Type SelectInfo)
{
	if (!ProposedSelection.IsValid())
	{
		if (SelectInfo == ESelectInfo::Direct)
		{
			return;
		}
			
		ProposedSelection = SelectedItem;
	}
	// Ensure that the proposed selection is different
	if(SelectInfo != ESelectInfo::OnNavigation)
	{
		// Ensure that the proposed selection is different from selected
		if ( ProposedSelection != SelectedItem )
		{
			PlaySelectionChangeSound();
			SelectedItem = ProposedSelection;
			OnSelectionChanged.ExecuteIfBound( ProposedSelection, SelectInfo );
		}
		// close combo even if user reselected item
		this->SetIsOpen( false );
	}
}

FReply SMapModeComboBox::OnButtonRightClick()
{
	// if user clicked to close the combo menu
	if (this->IsOpen())
	{
		// Re-select first selected item, just in case it was selected by navigation previously
		TArray<TSharedPtr<EMapMode>> SelectedItems = ComboListView->GetSelectedItems();
		if (SelectedItems.Num() > 0)
		{
			OnSelectionChanged_Internal(SelectedItems[0], ESelectInfo::Direct);
		}
	}
	else
	{
		PlayPressedSound();
		OnComboBoxOpening.ExecuteIfBound();
	}

	return SComboButton::OnButtonClicked();
}

FReply SMapModeComboBox::OnButtonClicked()
{
	if (OnLeftMouseClick.IsBound())
	{
		OnLeftMouseClick.Execute(SelectedItem);
	}
	return FReply::Handled();
}

FReply SMapModeComboBox::OnKeyDownHandler(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Enter)
	{
		// Select the first selected item on hitting enter
		TArray<TSharedPtr<EMapMode>> SelectedItems = ComboListView->GetSelectedItems();
		if (SelectedItems.Num() > 0)
		{
			OnSelectionChanged_Internal(SelectedItems[0], ESelectInfo::OnKeyPress);
			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}

void SMapModeComboBox::PlayPressedSound() const
{
	FSlateApplication::Get().PlaySound( PressedSound );
}

void SMapModeComboBox::PlaySelectionChangeSound() const
{
	FSlateApplication::Get().PlaySound( SelectionChangeSound );
}

UMapModeComboBox::UMapModeComboBox()
{
PRAGMA_DISABLE_DEPRECATION_WARNINGS
	// We don't want to try and load fonts on the server.
	WidgetStyle = FComboBoxStyle();
	ItemStyle = FTableRowStyle();
	ScrollBarStyle = FScrollBarStyle();

	ContentPadding = FMargin(4.0, 2.0);
	ForegroundColor = ItemStyle.TextColor;

	MaxListHeight = 450.0f;
	bHasDownArrow = true;
	bEnableGamepadNavigationMode = true;
	bIsFocusable = true;
PRAGMA_ENABLE_DEPRECATION_WARNINGS
}


void UMapModeComboBox::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyComboBox.Reset();
	ComboBoxContent.Reset();
}


TSharedRef<SWidget> UMapModeComboBox::RebuildWidget()
{
PRAGMA_DISABLE_DEPRECATION_WARNINGS
	MyComboBox =
		SNew(SMapModeComboBox)
		.ComboBoxStyle(&WidgetStyle)
		.ItemStyle(&ItemStyle)
		.ForegroundColor(ForegroundColor)
		.OptionsSource(&Options)
		.InitiallySelectedItem(SelectedOption)
		.ContentPadding(ContentPadding)
		.MaxListHeight(MaxListHeight)
		.HasDownArrow(bHasDownArrow)
		.EnableGamepadNavigationMode(bEnableGamepadNavigationMode)
		.OnLeftMouseClick_UObject(this, &UMapModeComboBox::HandleLeftMouseClick)
		.OnGenerateWidget_UObject(this, &UMapModeComboBox::HandleGenerateItemWidget)
		.OnSelectionChanged_UObject(this, &UMapModeComboBox::HandleSelectionChanged)
		.OnComboBoxOpening_UObject(this, &UMapModeComboBox::HandleOpening)
		.IsFocusable(bIsFocusable)
		.ScrollBarStyle(&ScrollBarStyle)
		[
			SAssignNew(ComboBoxContent, SBox)
		];
PRAGMA_ENABLE_DEPRECATION_WARNINGS

	GenerateContent();

	return MyComboBox.ToSharedRef();
}


void UMapModeComboBox::AddOption(EMapMode Key)
{
	TSharedPtr<EMapMode> Option = MakeShared<EMapMode>();
	*Option.Get() = Key;
	if (Options.AddUnique(Option) >= 0)
	{
		if (MyComboBox)
		{
			MyComboBox->RefreshOptions();
		}
	}
}


bool UMapModeComboBox::RemoveOption(EMapMode Key)
{
	TSharedPtr<EMapMode> Option = MakeShared<EMapMode>();
	*Option.Get() = Key;
	
	bool bResult = Options.RemoveSingle(Option) > 0;
	if (bResult)
	{
		if (Option == SelectedOption)
		{
			ClearSelection();
		}

		if (MyComboBox)
		{
			MyComboBox->RefreshOptions();
		}
	}
	return bResult;
}


void UMapModeComboBox::ClearOptions()
{
	Options.Reset();
	ClearSelection();
	if (MyComboBox)
	{
		MyComboBox->RefreshOptions();
	}
}


void UMapModeComboBox::ClearSelection()
{
	if (MyComboBox)
	{
		MyComboBox->ClearSelection();
	}
}


void UMapModeComboBox::SetSelectedOption(EMapMode Option)
{
	TSharedPtr<EMapMode> ProperOption = MakeShared<EMapMode>();
	*ProperOption.Get() = Option;
	
	if (SelectedOption != ProperOption)
	{
		if (MyComboBox)
		{
			MyComboBox->SetSelectedItem(ProperOption);
		}
		else
		{
			SelectedOption = ProperOption;
		}
	}
}

EMapMode UMapModeComboBox::GetSelectedOption() const
{
	return *SelectedOption.Get();
}


bool UMapModeComboBox::IsOpen() const
{
	return MyComboBox && MyComboBox->IsOpen();
}

PRAGMA_DISABLE_DEPRECATION_WARNINGS
void  UMapModeComboBox::SetContentPadding(FMargin InPadding)
{
	ContentPadding = InPadding;
	if (MyComboBox.IsValid())
	{
		MyComboBox->SetButtonContentPadding(InPadding);
	}
}

FMargin  UMapModeComboBox::GetContentPadding() const
{
	return ContentPadding;
}

void UMapModeComboBox::SetEnableGamepadNavigationMode(bool InEnableGamepadNavigationMode)
{
	bEnableGamepadNavigationMode = InEnableGamepadNavigationMode;
	if (MyComboBox.IsValid())
	{
		MyComboBox->SetEnableGamepadNavigationMode(bEnableGamepadNavigationMode);
	}
}

bool UMapModeComboBox::IsEnableGamepadNavigationMode() const
{
	return bEnableGamepadNavigationMode;
}

bool UMapModeComboBox::IsHasDownArrow() const
{
	return bHasDownArrow;
}

void UMapModeComboBox::SetHasDownArrow(bool InHasDownArrow)
{
	bHasDownArrow = InHasDownArrow;
	if (MyComboBox.IsValid())
	{
		MyComboBox->SetHasDownArrow(InHasDownArrow);
	}
}

float UMapModeComboBox::GetMaxListHeight() const
{
	return MaxListHeight;
}

void UMapModeComboBox::SetMaxListHeight(float InMaxHeight)
{
	MaxListHeight = InMaxHeight;
	if (MyComboBox.IsValid())
	{
		MyComboBox->SetMaxHeight(MaxListHeight);
	}
}

const FComboBoxStyle& UMapModeComboBox::GetWidgetStyle() const
{
	return WidgetStyle;
}

const FTableRowStyle& UMapModeComboBox::GetItemStyle() const
{
	return ItemStyle;
}

const FScrollBarStyle& UMapModeComboBox::GetScrollBarStyle() const
{
	return ScrollBarStyle;
}

bool UMapModeComboBox::IsFocusable() const
{
	return bIsFocusable;
}

FSlateColor UMapModeComboBox::GetForegroundColor() const
{
	return ForegroundColor;
}

void UMapModeComboBox::SetWidgetStyle(const FComboBoxStyle& InWidgetStyle)
{
	WidgetStyle = InWidgetStyle;
	if (MyComboBox.IsValid())
	{
		MyComboBox->InvalidateStyle();
	}
}

void UMapModeComboBox::SetItemStyle(const FTableRowStyle& InItemStyle)
{
	ItemStyle = InItemStyle;
	if (MyComboBox.IsValid())
	{
		MyComboBox->InvalidateItemStyle();
	}
}

void UMapModeComboBox::InitScrollBarStyle(const FScrollBarStyle& InScrollBarStyle)
{
	ensureMsgf(!MyComboBox.IsValid(), TEXT("The widget is already created."));
	ScrollBarStyle = InScrollBarStyle;
}

void UMapModeComboBox::InitIsFocusable(bool InIsFocusable)
{
	ensureMsgf(!MyComboBox.IsValid(), TEXT("The widget is already created."));
	bIsFocusable = InIsFocusable;
}

void UMapModeComboBox::InitForegroundColor(FSlateColor InForegroundColor)
{
	ensureMsgf(!MyComboBox.IsValid(), TEXT("The widget is already created."));
	ForegroundColor = InForegroundColor;
}
PRAGMA_ENABLE_DEPRECATION_WARNINGS

void UMapModeComboBox::GenerateContent()
{
	bool bSetToNull = true;
	if (IsDesignTime())
	{
		ComboBoxContent->SetContent(SNew(STextBlock).Text(FText::AsNumber(static_cast<int32>(*SelectedOption))));
		bSetToNull = false;
	}
	else
	{
		// Call the user's delegate to see if they want to generate a custom widget bound to the data source.
		if (OnGenerateContentWidget.IsBound())
		{
			if (UWidget* Widget = OnGenerateContentWidget.Execute(*SelectedOption))
			{
				ComboBoxContent->SetContent(Widget->TakeWidget());
				bSetToNull = false;
			}
		}
		else
		{
			// Warn the user that they need to generate a widget for the item
			ComboBoxContent->SetContent(
				SNew(STextBlock)
				.Text(FText::Format(LOCTEXT("WarningMissingOnGenerateContentWidget", "{0} Missing OnGenerateContentWidget"), static_cast<int32>(*SelectedOption)))
				);
			bSetToNull = false;
		}
	}

	if (bSetToNull)
	{
		ComboBoxContent->SetContent(SNullWidget::NullWidget);
	}
}


TSharedRef<SWidget> UMapModeComboBox::HandleGenerateItemWidget(TSharedPtr<EMapMode> Item)
{
	if (IsDesignTime())
	{
		return SNew(STextBlock).Text(FText::AsNumber(static_cast<int32>(*SelectedOption.Get())));
	}
	else
	{
		// Call the user's delegate to see if they want to generate a custom widget bound to the data source.
		if (OnGenerateItemWidget.IsBound())
		{
			if (UWidget* Widget = OnGenerateItemWidget.Execute(*Item))
			{
				return Widget->TakeWidget();
			}
			else
			{
				return SNullWidget::NullWidget;
			}
		}
	}

	return SNew(STextBlock)
		.Text(FText::Format(LOCTEXT("WarningMissingOnGenerateItemWidget", "{0} Missing OnGenerateItemWidget"), FText::AsNumber(static_cast<int32>(*SelectedOption))));
}


void UMapModeComboBox::HandleSelectionChanged(TSharedPtr<EMapMode> Item, ESelectInfo::Type SelectionType)
{
	if (SelectedOption != Item)
	{
		SelectedOption = Item;

		if (!IsDesignTime())
		{
			OnSelectionChanged.Broadcast(*Item, SelectionType);
		}
		GenerateContent();
	}
}

void UMapModeComboBox::HandleOpening()
{
	if (!IsDesignTime())
	{
		OnOpening.Broadcast();
	}
}

void UMapModeComboBox::HandleLeftMouseClick(TSharedPtr<EMapMode> MapMode)
{
	if (OnLeftMouseClick.IsBound())
	{
		OnLeftMouseClick.Execute(*MapMode);
	}
}

#if WITH_EDITOR

const FText UMapModeComboBox::GetPaletteCategory()
{
	return LOCTEXT("Input", "Input");
}

#endif

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE

