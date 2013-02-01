#include "editbox.h"
#include "handlermethod.h"
#include "caret.h"
#include "numericutils.h"

// ----------------------------------------------------------------------------
// EditBox::EditBox
// EditBox class constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C EditBox::EditBox()
: EmptyText(_L("Input text"))
, Color(TRgb(200, 200, 200))
, EmptyColor(TRgb(120, 120, 120))
, BackgroundColor(TRgb(0, 0, 0, 0))
, Align(Alignment::EHLeftVMid)
, CornerRadius(5)
, BorderSize(1)
, BorderColor(TRgb(80, 80, 80))
, CaretOffset(0)
    {
    Text.ValueChanged += MethodHandler(this, &EditBox::Text_Changed);
    Font.ValueChanged += MethodHandler(this, &EditBox::Font_Changed);
    Color.ValueChanged += MethodHandler(this, &EditBox::Color_Changed);
    BackgroundColor.ValueChanged += MethodHandler(this, &EditBox::BackgroundColor_Changed);
    Align.ValueChanged += MethodHandler(this, &EditBox::Align_Changed);
    CornerRadius.ValueChanged += MethodHandler(this, &EditBox::CornerRadius_Changed);
    ClientRectangle.ValueChanged += MethodHandler(this, &EditBox::ClientRect_Changed);
    BorderSize.ValueChanged += MethodHandler(this, &EditBox::BorderSize_Changed);
    Focused.ValueChanged += MethodHandler(this, &EditBox::Focused_Changed);
    CaretOffset.ValueChanged += MethodHandler(this, &EditBox::CaretOffset_Changed);
    TextBounds.ValueChanged += MethodHandler(this, &EditBox::TextBounds_Changed);
    EmptyTextBounds.ValueChanged += MethodHandler(this, &EditBox::EmptyTextBounds_Changed);
    CaretBounds.ValueChanged += MethodHandler(this, &EditBox::CaretBounds_Changed);
    ScrollOffset.ValueChanged += MethodHandler(this, &EditBox::ScrollOffset_Changed);

    CanFocus = ETrue;
    Capture = ETrue;

    _textDrawer = &EditBox::DrawEmptyText;
    _borderDrawer = &EditBox::DrawSolidBorder;

    _caret = new (ELeave) Caret();
    AddControl(_caret);
    _caret->Visible = EFalse;
    }

// ----------------------------------------------------------------------------
// EditBox::EditBox
// EditBox class destructor.
// ----------------------------------------------------------------------------
//
EXPORT_C EditBox::~EditBox()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// EditBox::OnPaint
// Override from Control. Draws the button to the UI.
// ----------------------------------------------------------------------------
//
EXPORT_C void EditBox::OnPaint(PaintEventArgs& aArgs)
    {
    CBitmapContext& gc = aArgs.Graphics();

    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(BackgroundColor);
    (this->*_borderDrawer)(gc);
    gc.DrawRoundRect(ClientRectangle, TSize(CornerRadius, CornerRadius));

    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetPenSize(TSize(1, 1));
    gc.UseFont(Font);
    gc.SetClippingRect(DisplayRectangle);
    (this->*_textDrawer)(gc);
    gc.CancelClippingRect();
    gc.DiscardFont();

    Control::OnPaint(aArgs);
    }

// ----------------------------------------------------------------------------
// EditBox::OnMouseDown
// Override from Control. Handles MouseDown event.
// ----------------------------------------------------------------------------
//
EXPORT_C void EditBox::OnMouseDown(MouseEventArgs& aArgs)
    {
    Control::OnMouseDown(aArgs);
    }

// ----------------------------------------------------------------------------
// EditBox::OnKeyPress
// Override from Control. Handles KeyPress event.
// ----------------------------------------------------------------------------
//
EXPORT_C void EditBox::OnKeyPress(KeyPressEventArgs& aArgs)
    {
    TChar character = aArgs.KeyChar();
    InputChar(character);
    aArgs.Handled = ETrue;
    Control::OnKeyPress(aArgs);
    }

// ----------------------------------------------------------------------------
// EditBox::Text_Changed
// Handler for Text property change.
// ----------------------------------------------------------------------------
//
void EditBox::Text_Changed(const PropertyBase<const TDesC&>& /*aText*/)
    {
    if (Text->Length() == 0)
        {
        _textDrawer = &EditBox::DrawEmptyText;
        }
    else
        {
        _textDrawer = &EditBox::DrawUserText;
        }
    CaretOffset = NumericUtils::SnapToInterval(CaretOffset(), 0, Text->Length());
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// EditBox::Font_Changed
// Handler for Font property change.
// ----------------------------------------------------------------------------
//
void EditBox::Font_Changed(const PropertyBase<const CFont*>& /*aFont*/)
    {
    if (NULL != Font)
        {
        _fontAscent = Font->FontMaxAscent();
        }
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// EditBox::Color_Changed
// Handler for Color property change.
// ----------------------------------------------------------------------------
//
void EditBox::Color_Changed(const PropertyBase<TRgb>& /*aColor*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// EditBox::BackgroundColor_Changed
// Handler for BackgroundColor property change.
// ----------------------------------------------------------------------------
//
void EditBox::BackgroundColor_Changed(const PropertyBase<TRgb>& /*aColor*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// EditBox::Align_Changed
// Handler for Align property change.
// ----------------------------------------------------------------------------
//
void EditBox::Align_Changed(const PropertyBase<Alignment::Align>& /*aAlignment*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// EditBox::CornerRadius_Changed
// Handler for CornerRadius property change.
// ----------------------------------------------------------------------------
//
void EditBox::CornerRadius_Changed(const PropertyBase<TInt>& /*aCornerRadius*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// EditBox::ClientRect_Changed
// Handler for ClientRectangle property change.
// ----------------------------------------------------------------------------
//
void EditBox::ClientRect_Changed(const PropertyBase<TRect>& /*aClientRect*/)
    {
    TRect displayRect = ClientRectangle;
    displayRect.Grow(-5, -5);
    DisplayRectangle = displayRect;
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// EditBox::BorderSize_Changed
// Handlers BorderSize property changes
// ----------------------------------------------------------------------------
//
void EditBox::BorderSize_Changed(const PropertyBase<TInt>& /*aBorderSize*/)
    {
    if (BorderSize > 0)
        {
        _borderDrawer = &EditBox::DrawSolidBorder;
        }
    else
        {
        _borderDrawer = &EditBox::DrawNullBorder;
        }
    }

// ----------------------------------------------------------------------------
// EditBox::Focused_Changed
// Handles Focused property changed. Makes caret visible or not.
// ----------------------------------------------------------------------------
//
void EditBox::Focused_Changed(const PropertyBase<TBool>& /*aFocused*/)
    {
    _caret->Visible = Focused;
    }

// ----------------------------------------------------------------------------
// EditBox::CaretOffset
// Handles CaretOffset property change.
// ----------------------------------------------------------------------------
//
void EditBox::CaretOffset_Changed(const PropertyBase<TInt>& /*aCaretOffset*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// EditBox::TextBounds_Changed
// Handles TextBounds property change.
// ----------------------------------------------------------------------------
//
void EditBox::TextBounds_Changed(const PropertyBase<TRect>& /*aBounds*/)
    {
    _textPosition = TextBounds().iTl;
    _textPosition.iY += _fontAscent;
    _textPosition.iX += ScrollOffset;
    }

// ----------------------------------------------------------------------------
// EditBox::EmptyTextBounds_Changed
// Handles EmptyTextBounds property change.
// ----------------------------------------------------------------------------
//
void EditBox::EmptyTextBounds_Changed(const PropertyBase<TRect>& /*aBounds*/)
    {
    _emptyTextPosition = EmptyTextBounds().iTl;
    _emptyTextPosition.iY += _fontAscent;
    }

// ----------------------------------------------------------------------------
// EditBox::CaretBounds_Changed
// Handles CaretBounds property change.
// ----------------------------------------------------------------------------
//
void EditBox::CaretBounds_Changed(const PropertyBase<TRect>& /*aCaretBounds*/)
    {
    TRect caretBounds = CaretBounds;
    caretBounds.Move(ScrollOffset, 0);
    _caret->Bounds = caretBounds;
    }

// ----------------------------------------------------------------------------
// EditBox::ScrollOffset_Changed
// Handles ScrollOffset property change.
// ----------------------------------------------------------------------------
//
void EditBox::ScrollOffset_Changed(const PropertyBase<TInt>& /*aScrollOffset*/)
    {
    TextBounds_Changed(TextBounds);
    CaretBounds_Changed(CaretBounds);
    }

// ----------------------------------------------------------------------------
// EditBox::Layout
// Performs internal layout. Calculates text position, etc.
// ----------------------------------------------------------------------------
//
void EditBox::Layout()
    {
    const CFont* font = Font;
    if (!font)
        return;

    TRect displayRect = DisplayRectangle;

    TSize textSize(font->TextWidthInPixels(Text), font->FontMaxHeight());
    TRect textRect(displayRect.iTl, textSize);
    textRect.Move(DoAlign(Align, displayRect.Size(), textSize));
    TextBounds = textRect;

    textSize.iWidth = font->TextWidthInPixels(EmptyText);
    textRect.SetRect(displayRect.iTl, textSize);
    textRect.Move(DoAlign(Align, displayRect.Size(), textSize));
    EmptyTextBounds = textRect;

    CalculateCaretBounds();
    CalculateScrollOffset();

    Invalidate();
    }

// ----------------------------------------------------------------------------
// EditBox::CalculateCaretBounds
// Calculates the caret bounds.
// ----------------------------------------------------------------------------
//
void EditBox::CalculateCaretBounds()
    {
    TPtrC textToCaret(Text->Ptr(), CaretOffset);
    TPoint caretLocation(Font->TextWidthInPixels(textToCaret),0);
    caretLocation += TextBounds().iTl;

    CaretBounds = TRect(caretLocation, TSize(_caret->CaretWidth, TextBounds().Height()));
    Invalidate();
    }

// ----------------------------------------------------------------------------
// EditBox::CalculateScrollOffset
// Calculates the scroll offset based on caret position.
// ----------------------------------------------------------------------------
//
void EditBox::CalculateScrollOffset()
    {
    TInt scrollOffset = ScrollOffset;
    TRect displayRect = DisplayRectangle;
    TRect caretRect = _caret->Bounds;

    if (caretRect.iTl.iX < displayRect.iTl.iX)
        {
        // The caret is on the left side
        scrollOffset += (displayRect.iTl.iX - caretRect.iTl.iX);
        }
    else if (caretRect.iBr.iX > displayRect.iBr.iX)
        {
        // The caret is on the right side
        scrollOffset += (displayRect.iBr.iX - caretRect.iBr.iX);
        }
    else
        {
        // Check if the text is scrolled to the left, but there is empty room on the right
        TInt textRightLimit = TextBounds().iBr.iX + scrollOffset + caretRect.Width();
        if ((scrollOffset < 0) && (textRightLimit < displayRect.iBr.iX))
            {
            scrollOffset = Min(0, scrollOffset + (displayRect.iBr.iX - textRightLimit));
            }
        }

    if (scrollOffset != ScrollOffset)
        {
        ScrollOffset = scrollOffset;
        Invalidate();
        }
    }

// ----------------------------------------------------------------------------
// EditBox::DrawEmptyText
// Draws the empty text on the screen.
// ----------------------------------------------------------------------------
//
void EditBox::DrawEmptyText(CBitmapContext& aGc)
    {
    aGc.SetPenColor(EmptyColor);
    aGc.DrawText(EmptyText, _emptyTextPosition);
    }

// ----------------------------------------------------------------------------
// EditBox::DrawUserText
// Draws the text on the screen.
// ----------------------------------------------------------------------------
//
void EditBox::DrawUserText(CBitmapContext& aGc)
    {
    aGc.SetPenColor(Color);
    aGc.DrawText(Text, _textPosition);
    }

// ----------------------------------------------------------------------------
// EditBox::DrawSolidBorder
// Sets up the graphic context to draw a solid border.
// ----------------------------------------------------------------------------
//
void EditBox::DrawSolidBorder(CBitmapContext& aGc)
    {
    aGc.SetPenStyle(CGraphicsContext::ESolidPen);
    aGc.SetPenColor(BorderColor);
    aGc.SetPenSize(TSize(BorderSize, BorderSize));
    }

// ----------------------------------------------------------------------------
// EditBox::DrawNullBorder
// Sets up the graphic context not to draw any border.
// ----------------------------------------------------------------------------
//
void EditBox::DrawNullBorder(CBitmapContext& aGc)
    {
    aGc.SetPenStyle(CGraphicsContext::ENullPen);
    }

// ----------------------------------------------------------------------------
// EditBox::InputChar
// Inputs a character to the edit box.
// ----------------------------------------------------------------------------
//
void EditBox::InputChar(const TChar& aChar)
    {
    if (aChar.IsPrint())
        {
        LString text = Text();
        LString charDes;
        charDes.AppendL(aChar);
        text.InsertL(CaretOffset, charDes);
        Text = text;
        CaretOffset = CaretOffset + 1;
        }
    else
        {
        InputControlChar(aChar);
        }
    }

// ----------------------------------------------------------------------------
// EditBox::InputControlChar
// Inputs a control character to the edit box.
// ----------------------------------------------------------------------------
//
void EditBox::InputControlChar(const TChar& aChar)
    {
    switch (aChar)
        {
        case EKeyLeftArrow:
            {
            CaretOffset = NumericUtils::SnapToInterval(CaretOffset - 1, 0, Text->Length());
            break;
            }
        case EKeyRightArrow:
            {
            CaretOffset = NumericUtils::SnapToInterval(CaretOffset + 1, 0, Text->Length());
            break;
            }
        case EKeyBackspace:
            {
            if (CaretOffset > 0)
                {
                LString text = Text();
                text.Delete(CaretOffset - 1, 1);
                CaretOffset = CaretOffset - 1;
                Text = text;
                }
            break;
            }
        case EKeyDelete:
            {
            if (Text->Length() > CaretOffset)
                {
                LString text = Text();
                text.Delete(CaretOffset, 1);
                Text = text;
                }
            break;
            }
        default:
            {
            break;
            }
        }
    }
