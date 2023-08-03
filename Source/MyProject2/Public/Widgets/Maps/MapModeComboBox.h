#pragma once
#include "Maps/MapController.h"
#include "Widgets/Input/SComboBox.h"
#include "MapModeComboBox.generated.h"

DECLARE_DELEGATE(FOnComboBoxOpening)

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLeftMouseClick, EMapMode, MapMode);

class SMapModeComboRow : public SComboRow<TSharedPtr<EMapMode>>
{
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
};

class SMapModeComboBox : public SComboButton
{
public:
	DECLARE_DELEGATE_OneParam(FOnLeftMouseClick, TSharedPtr<EMapMode>)

	typedef typename TSlateDelegates<TSharedPtr<EMapMode>>::FOnGenerateWidget FOnGenerateWidget;
	typedef typename TSlateDelegates<TSharedPtr<EMapMode>>::FOnSelectionChanged FOnSelectionChanged;
	
	SLATE_BEGIN_ARGS( SMapModeComboBox );

		/** Slot for this button's content (optional) */
		SLATE_DEFAULT_SLOT( FArguments, Content )

		SLATE_STYLE_ARGUMENT( FComboBoxStyle, ComboBoxStyle )

		/** The visual style of the button part of the combo box (overrides ComboBoxStyle) */
		SLATE_STYLE_ARGUMENT( FButtonStyle, ButtonStyle )

		SLATE_STYLE_ARGUMENT(FTableRowStyle, ItemStyle)
		
		SLATE_STYLE_ARGUMENT( FScrollBarStyle, ScrollBarStyle )

		SLATE_ATTRIBUTE( FMargin, ContentPadding )
		SLATE_ATTRIBUTE( FSlateColor, ForegroundColor )

		SLATE_ARGUMENT( const TArray<TSharedPtr<EMapMode>>*, OptionsSource )
		SLATE_EVENT( FOnSelectionChanged, OnSelectionChanged )
		SLATE_EVENT( FOnGenerateWidget, OnGenerateWidget )
		SLATE_EVENT( FOnLeftMouseClick, OnLeftMouseClick )

		/** Called when combo box is opened, before list is actually created */
		SLATE_EVENT( FOnComboBoxOpening, OnComboBoxOpening )

		/** The custom scrollbar to use in the ListView */
		SLATE_ARGUMENT(TSharedPtr<SScrollBar>, CustomScrollbar)

		/** The option that should be selected when the combo box is first created */
		SLATE_ARGUMENT( TSharedPtr<EMapMode>, InitiallySelectedItem )

		SLATE_ARGUMENT( TOptional<EPopupMethod>, Method )

		/** The max height of the combo box menu */
		SLATE_ARGUMENT(float, MaxListHeight)

		/** The sound to play when the button is pressed (overrides ComboBoxStyle) */
		SLATE_ARGUMENT( TOptional<FSlateSound>, PressedSoundOverride )

		/** The sound to play when the selection changes (overrides ComboBoxStyle) */
		SLATE_ARGUMENT( TOptional<FSlateSound>, SelectionChangeSoundOverride )

		/**
		 * When false, the down arrow is not generated and it is up to the API consumer
		 * to make their own visual hint that this is a drop down.
		 */
		SLATE_ARGUMENT( bool, HasDownArrow )

		/**
		 *  When false, directional keys will change the selection. When true, ComboBox
		 *	must be activated and will only capture arrow input while activated.
		*/
		SLATE_ARGUMENT(bool, EnableGamepadNavigationMode)

		/** When true, allows the combo box to receive keyboard focus */
		SLATE_ARGUMENT( bool, IsFocusable )

		/** True if this combo's menu should be collapsed when our parent receives focus, false (default) otherwise */
		SLATE_ARGUMENT(bool, CollapseMenuOnParentFocus)
				
	SLATE_END_ARGS()

	/**
	 * Construct the widget from a declaration
	 *
	 * @param InArgs   Declaration from which to construct the combo box
	 */
	void Construct( const FArguments& InArgs );

	SMapModeComboBox();

#if WITH_ACCESSIBILITY
		protected:
		friend class FSlateAccessibleComboBox;
		/**
		* An accessible implementation of SComboBox to expose to platform accessibility APIs.
		* We inherit from IAccessibleProperty as Windows will use the interface to read out 
		* the value associated with the combo box. Convenient place to return the value of the currently selected option. 
		* For subclasses of SComboBox, inherit and override the necessary functions
		*/
		class FSlateAccessibleComboBox
			: public FSlateAccessibleWidget
			, public IAccessibleProperty
		{
		public:
			FSlateAccessibleComboBox(TWeakPtr<SWidget> InWidget);

			// IAccessibleWidget
			virtual IAccessibleProperty* AsProperty() override;
			// ~

			// IAccessibleProperty
			virtual FString GetValue() const override;

			virtual FVariant GetValueAsVariant() const override;
			// ~
		};

		public:
		virtual TSharedRef<FSlateAccessibleWidget> CreateAccessibleWidget() override;

	virtual TOptional<FText> GetDefaultAccessibleText(EAccessibleType AccessibleType) const;
#endif

	void ClearSelection( );

	void SetSelectedItem(TSharedPtr<EMapMode> InSelectedItem);

	void SetEnableGamepadNavigationMode(bool InEnableGamepadNavigationMode);

	void SetMaxHeight(float InMaxHeight);

	void SetStyle(const FComboBoxStyle* InStyle);

	void InvalidateStyle();

	void SetItemStyle(const FTableRowStyle* InItemStyle);

	void InvalidateItemStyle();

	/** @return the item currently selected by the combo box. */
	TSharedPtr<EMapMode> GetSelectedItem();


	/** 
	 * Requests a list refresh after updating options 
	 * Call SetSelectedItem to update the selected item if required
	 * @see SetSelectedItem
	 */
	void RefreshOptions();

protected:
	/** Handle key presses that SListView ignores */
	FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;

	virtual bool SupportsKeyboardFocus() const override;

	virtual bool IsInteractable() const;

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

private:

	/** Generate a row for the InItem in the combo box's list (passed in as OwnerTable). Do this by calling the user-specified OnGenerateWidget */
	TSharedRef<ITableRow> GenerateMenuItemRow(TSharedPtr<EMapMode> InItem, const TSharedRef<STableViewBase>& OwnerTable);

	//** Called if the menu is closed
	void OnMenuOpenChanged(bool bOpen);

	/** Invoked when the selection in the list changes */
	void OnSelectionChanged_Internal(TSharedPtr<EMapMode> ProposedSelection, ESelectInfo::Type SelectInfo);

	FReply OnButtonRightClick();

	/** Handle clicking on the content menu */
	virtual FReply OnButtonClicked() override;

	FReply OnKeyDownHandler(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);


	/** Play the pressed sound */
	void PlayPressedSound() const;

	/** Play the selection changed sound */
	void PlaySelectionChangeSound() const;

	/** The Sound to play when the button is pressed */
	FSlateSound PressedSound;

	/** The Sound to play when the selection is changed */
	FSlateSound SelectionChangeSound;

	/** The item style to use. */
	const FTableRowStyle* ItemStyle;

	/** The combo box style to use. */
	const FComboBoxStyle* ComboBoxStyle;
	
	/** The padding around each menu row */
	FMargin MenuRowPadding;

private:
	FOnLeftMouseClick OnLeftMouseClick;
	
	/** Delegate that is invoked when the selected item in the combo box changes */
	FOnSelectionChanged OnSelectionChanged;
	/** The item currently selected in the combo box */
	TSharedPtr<EMapMode> SelectedItem;
	/** The ListView that we pop up; visualized the available options. */
	TSharedPtr< SListView<TSharedPtr<EMapMode>> > ComboListView;
	/** The Scrollbar used in the ListView. */
	TSharedPtr< SScrollBar > CustomScrollbar;
	/** Delegate to invoke before the combo box is opening. */
	FOnComboBoxOpening OnComboBoxOpening;
	/** Delegate to invoke when we need to visualize an option as a widget. */
	FOnGenerateWidget OnGenerateWidget;
	// Use activate button to toggle ListView when enabled
	bool EnableGamepadNavigationMode;
	// Holds a flag indicating whether a controller/keyboard is manipulating the combobox's value. 
	// When true, navigation away from the widget is prevented until a new value has been accepted or canceled. 
	bool bControllerInputCaptured;

	TSharedPtr<SBox> ComboBoxMenuContent;

	const TArray<TSharedPtr<EMapMode>>* OptionsSource;
	
};


UCLASS(meta = (DisplayName = "ComboBox (Key)"))
class MYPROJECT2_API UMapModeComboBox : public UWidget
{
	GENERATED_BODY()

public:
	UMapModeComboBox();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectionChangedEvent, EMapMode, SelectedItem, ESelectInfo::Type, SelectionType);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpeningEvent);
	DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UWidget*, FGenerateWidgetEvent, EMapMode, Item);

private:
	TArray<TSharedPtr<EMapMode>> Options;

	TSharedPtr<EMapMode> SelectedOption;

public:
	UE_DEPRECATED(5.2, "Direct access to WidgetStyle is deprecated. Please use the getter or setter.")
	/** The combobox style. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Style, meta = (DisplayName = "Style"))
	FComboBoxStyle WidgetStyle;

	UE_DEPRECATED(5.2, "Direct access to ItemStyle is deprecated. Please use the getter or setter.")
	/** The item row style. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Style)
	FTableRowStyle ItemStyle;

	UE_DEPRECATED(5.2, "Direct access to ScrollBarStyle is deprecated. Please use the getter. Note that this property is only set at construction and is not modifiable at runtime.")
	/** The scroll bar style. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category="Style")
    FScrollBarStyle ScrollBarStyle;

	UE_DEPRECATED(5.2, "Direct access to ForegroundColor is deprecated. Please use the getter. Note that this property is only set at construction and is not modifiable at runtime.")
	/** The foreground color to pass through the hierarchy. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category = Style, meta = (DesignerRebuild))
	FSlateColor ForegroundColor;

	UE_DEPRECATED(5.2, "Direct access to ContentPadding is deprecated. Please use the getter or setter.")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Style)
	FMargin ContentPadding;

	UE_DEPRECATED(5.2, "Direct access to MaxListHeight is deprecated. Please use the getter or setter.")
	/** The max height of the combobox list that opens */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Style, AdvancedDisplay)
	float MaxListHeight;

	UE_DEPRECATED(5.2, "Direct access to bHasDownArrow is deprecated. Please use the getter or setter.")
	/**
	 * When false, the down arrow is not generated and it is up to the API consumer
	 * to make their own visual hint that this is a drop down.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsHasDownArrow", Setter = "SetHasDownArrow", Category = Style, AdvancedDisplay)
	bool bHasDownArrow;

	UE_DEPRECATED(5.2, "Direct access to bEnableGamepadNavigationMode is deprecated. Please use the getter or setter.")
	/**
	 * When false, directional keys will change the selection. When true, ComboBox
	 * must be activated and will only capture arrow input while activated.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsEnableGamepadNavigationMode", Setter = "SetEnableGamepadNavigationMode", Category = Style, AdvancedDisplay)
	bool bEnableGamepadNavigationMode;

	UE_DEPRECATED(5.2, "Direct access to bIsFocusable is deprecated. Please use the getter. Note that this property is only set at construction and is not modifiable at runtime.")
	/** When true, allows the combo box to receive keyboard focus */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter = "IsFocusable", Category = Style)
	bool bIsFocusable;

public: // Events

	UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
	FOnLeftMouseClick OnLeftMouseClick;
	
	/** Called when the widget is needed for the content. */
	UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
	FGenerateWidgetEvent OnGenerateContentWidget;
	
	/** Called when the widget is needed for the item. */
	UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
	FGenerateWidgetEvent OnGenerateItemWidget;

	/** Called when a new item is selected in the combobox. */
	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnSelectionChangedEvent OnSelectionChanged;

	/** Called when the combobox is opening */
	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnOpeningEvent OnOpening;

public:
	
	/** Add an element to the option list. */
	UFUNCTION(BlueprintCallable, Category = "ComboBox")
	void AddOption(EMapMode Option);

	/** Remove an element to the option list. */
	UFUNCTION(BlueprintCallable, Category = "ComboBox")
	bool RemoveOption(EMapMode Option);

	/** Remove all the elements of the option list. */
	UFUNCTION(BlueprintCallable, Category = "ComboBox")
	void ClearOptions();

	/** Clear the current selection. */
	UFUNCTION(BlueprintCallable, Category = "ComboBox")
	void ClearSelection();

	/** Set the current selected option. */
	UFUNCTION(BlueprintCallable, Category = "ComboBox")
	void SetSelectedOption(EMapMode Option);

	/** Get the current selected option */
	UFUNCTION(BlueprintCallable, Category = "ComboBox")
	EMapMode GetSelectedOption() const;

	/** Is the combobox menu opened. */
	UFUNCTION(BlueprintCallable, Category = "ComboBox", Meta = (ReturnDisplayName = "bOpen"))
	bool IsOpen() const;

	//~ Begin UVisual Interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//~ End UVisual Interface

	/** Set the padding for content. */
	void SetContentPadding(FMargin InPadding);

	/** Get the padding for content. */
	FMargin GetContentPadding() const;

	/** Is the combobox navigated by gamepad. */
	bool IsEnableGamepadNavigationMode() const;

	/** Set whether the combobox is navigated by gamepad. */
	void SetEnableGamepadNavigationMode(bool InEnableGamepadNavigationMode);

	/** Is the combobox arrow showing. */
	bool IsHasDownArrow() const;

	/** Set whether the combobox arrow is showing. */
	void SetHasDownArrow(bool InHasDownArrow);

	/** Get the maximum height of the combobox list. */
	float GetMaxListHeight() const;

	/** Set the maximum height of the combobox list. */
	void SetMaxListHeight(float InMaxHeight);

	/** Get the style of the combobox. */
	const FComboBoxStyle& GetWidgetStyle() const;

	/** Set the style of the combobox. */
	void SetWidgetStyle(const FComboBoxStyle& InWidgetStyle);

	/** Get the style of the items. */
	const FTableRowStyle& GetItemStyle() const;

	/** Set the style of the items. */
	void SetItemStyle(const FTableRowStyle& InItemStyle);

	/** Get the style of the scrollbar. */
	const FScrollBarStyle& GetScrollBarStyle() const;

	/** Is the combobox focusable. */
	bool IsFocusable() const;

	/** Get the foreground color of the button. */
	FSlateColor GetForegroundColor() const;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:

	/** Initialize the scrollbar style in the constructor before the SWidget is constructed. */
	void InitScrollBarStyle(const FScrollBarStyle& InScrollBarStyle);

	/** Initialize IsFocusable in the constructor before the SWidget is constructed. */
	void InitIsFocusable(bool InIsFocusable);

	/** Initialize ForegroundColor in the constructor before the SWidget is constructed. */
	void InitForegroundColor(FSlateColor InForegroundColor);

private:
	/** Called by slate when it needs to generate the widget in the content box */
	void GenerateContent();

	/** Called by slate when it needs to generate a new item for the combobox */
	TSharedRef<SWidget> HandleGenerateItemWidget(TSharedPtr<EMapMode> Item);

	/** Called by slate when the underlying combobox selection changes */
	void HandleSelectionChanged(TSharedPtr<EMapMode> Item, ESelectInfo::Type SelectionType);

	/** Called by slate when the underlying combobox is opening */
	void HandleOpening();

	void HandleLeftMouseClick(TSharedPtr<EMapMode> MapMode);

	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface

private:
	/** A shared pointer to the underlying slate combobox */
	TSharedPtr<SMapModeComboBox> MyComboBox;

	/** A shared pointer to a container that holds the combobox content that is selected */
	TSharedPtr< SBox > ComboBoxContent;
};
