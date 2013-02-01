#include "button.h"
#include "handlermethod.h"
#include "application.h"
#include "fontsmanager.h"
#include "numericutils.h"
#include "debug.h"

// ----------------------------------------------------------------------------
// Button::Button
// Button class constructor.
// ----------------------------------------------------------------------------
//
Button::Button()
: Text(_L("Button"))
, Color(KRgbWhite)
, BackgroundColor(KRgbBlack)
, HighlightColor(TRgb(100, 100, 100))
, Align(Alignment::EHMidVMid)
, CornerRadius(10)
, BorderSize(1)
, BorderColor(TRgb(100, 100, 100))
, State(ENotPressed)
    {
    Font = Application::Instance()->Fonts->NormalFont();
    Text.ValueChanged += MethodHandler(this, &Button::Text_Changed);
    Font.ValueChanged += MethodHandler(this, &Button::Font_Changed);
    Color.ValueChanged += MethodHandler(this, &Button::Color_Changed);
    BackgroundColor.ValueChanged += MethodHandler(this, &Button::BackgroundColor_Changed);
    Align.ValueChanged += MethodHandler(this, &Button::Align_Changed);
    CornerRadius.ValueChanged += MethodHandler(this, &Button::CornerRadius_Changed);
    State.ValueChanged += MethodHandler(this, &Button::State_Changed);
    CanFocus = ETrue;
    Capture = ETrue;
    }

// ----------------------------------------------------------------------------
// Button::~Button
// Button class destructor.
// ----------------------------------------------------------------------------
//
Button::~Button()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// Button::OnPaint.
// Override from Control. Draws the button to the UI.
// ----------------------------------------------------------------------------
//
void Button::OnPaint(PaintEventArgs& aArgs)
    {
    CBitmapContext& gc = aArgs.Graphics();

    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    switch (State)
        {
        case ENotPressed:
            {
            gc.SetBrushColor(BackgroundColor);
            break;
            }
        case EPressed:
            {
            gc.SetBrushColor(HighlightColor);
            break;
            }
        }
    if (BorderSize > 0)
        {
        gc.SetPenStyle(CGraphicsContext::ESolidPen);
        gc.SetPenColor(BorderColor);
        gc.SetPenSize(TSize(BorderSize, BorderSize));
        }
    else
        {
        gc.SetPenStyle(CGraphicsContext::ENullPen);
        }
    gc.DrawRoundRect(ClientRectangle, TSize(CornerRadius, CornerRadius));

    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetPenSize(TSize(1, 1));
    gc.SetPenColor(Color);
    gc.UseFont(Font);
    gc.DrawText(Text, _textPosition);
    gc.DiscardFont();

    Control::OnPaint(aArgs);
    }

// ----------------------------------------------------------------------------
// Button::OnDragEnter
// From Control, raises the DragEnter event.
// ----------------------------------------------------------------------------
//
void Button::OnDragEnter(DragEventArgs& aArgs)
    {
    TRACE_FUNC_ENTRY;
    TRACE_INFO((_L("Button name: %S"), &Name()));
    Control::OnDragEnter(aArgs);
    if (aArgs.DragSource == this)
        {
        State = EPressed;
        }
    TRACE_FUNC_EXIT;
    }

// ----------------------------------------------------------------------------
// Button::OnDragLeave
// From Control, raises the DragLeave event.
// ----------------------------------------------------------------------------
//
void Button::OnDragLeave()
    {
    TRACE_FUNC_ENTRY;
    Control::OnDragLeave();
    State = ENotPressed;
    TRACE_FUNC_EXIT;
    }

// ----------------------------------------------------------------------------
// Button::Measure
// From Control, measures the necessary size for the control and children.
// ----------------------------------------------------------------------------
//
TSize Button::Measure(const TSize& aAvailableSize)
    {
    const CFont& font = *Font;
    TSize textSize(font.TextWidthInPixels(Text), font.FontMaxHeight());
    textSize += MarginsSize();
    textSize.iWidth += BorderSize + CornerRadius;
    textSize.iHeight += BorderSize + 2 * CornerRadius;
    textSize = NumericUtils::BoundingSize(textSize, MinimumSize);
    NumericUtils::LimitSize(textSize, aAvailableSize);
    PreferredSize = textSize;
    return textSize;
    }

// ----------------------------------------------------------------------------
// Button::Arrange
// Arranges the control.
// ----------------------------------------------------------------------------
//
TSize Button::Arrange(const TSize& aFinalSize)
    {
    const CFont& font = *Font;
    TSize textSize(font.TextWidthInPixels(Text), font.FontMaxHeight());
    TRect clientRect = ClientRectangle;

    _textPosition = DoAlign(Align, clientRect.Size(), textSize);
    _textPosition += clientRect.iTl;
    _textPosition.iY += font.FontMaxAscent();

    return aFinalSize;
    }

// ----------------------------------------------------------------------------
// Button::Text_Changed.
// Handler for Text property ValueChanged event.
// ----------------------------------------------------------------------------
//
void Button::Text_Changed(const PropertyBase<const TDesC&>& /*aText*/)
    {
    Arrange(Size);
    }

// ----------------------------------------------------------------------------
// Button::Font_Changed.
// Handler for Font property ValueChanged event.
// ----------------------------------------------------------------------------
//
void Button::Font_Changed(const PropertyBase<const CFont*>& /*aFont*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Button::Color_Changed.
// Handler for Color property ValueChanged event.
// ----------------------------------------------------------------------------
//
void Button::Color_Changed(const PropertyBase<TRgb>& /*aColor*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Button::BackgroundColor_Changed.
// Handler for BackgroundColor property ValueChanged event.
// ----------------------------------------------------------------------------
//
void Button::BackgroundColor_Changed(const PropertyBase<TRgb>& /*aBackgroundColor*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Button::Align_Changed.
// Handler for Align property ValueChanged event.
// ----------------------------------------------------------------------------
//
void Button::Align_Changed(const PropertyBase<Alignment::Align>& /*aAlign*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Button::CornerRadius_Changed.
// Handler for CornerRadius property ValueChanged event.
// ----------------------------------------------------------------------------
//
void Button::CornerRadius_Changed(const PropertyBase<TInt>& /*aCornerRadius*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Button::State_Changed
// Handler for State property ValueChanged event.
// ----------------------------------------------------------------------------
//
void Button::State_Changed(const PropertyBase<TState>& /*aState*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Button::Layout.
// Performs layout for inner button components.
// ----------------------------------------------------------------------------
//
void Button::Layout()
    {
    Arrange(Size);
    Control::Layout();
    }
