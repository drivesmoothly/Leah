#include "label.h"
#include "handlermethod.h"
#include "propertyadapters.h"
#include "propertybind.h"
#include "application.h"
#include "fontsmanager.h"
#include "numericutils.h"

/// Initialize static members
PropertyDes* const                  Label::TextProperty = NULL;
Property<const CFont*>* const       Label::FontProperty = NULL;
Property<TRgb>* const               Label::ColorProperty = NULL;
Property<TRgb>* const               Label::BackgroundColorProperty = NULL;
Property<HAlignment::Align>* const  Label::TextAlignmentProperty = NULL;

// ----------------------------------------------------------------------------
// Label::Label
// Constructor
// ----------------------------------------------------------------------------
//
EXPORT_C Label::Label()
: Text(*this, &Label::TextProperty, KNullDesC)
, Font(*this, &Label::FontProperty, NULL)
, Color(*this, &Label::ColorProperty, KRgbBlack)
, BackgroundColor(*this, &Label::BackgroundColorProperty, TRgb(0, 0, 0, 0))
, TextAlignment(*this, &Label::TextAlignmentProperty, HAlignment::ELeft)
    {
    Font = Application::Instance()->Fonts->NormalFont();
    TextAlignment.ValueChanged += MethodHandler(this, &Label::TextAlign_ValueChanged);
    Text.ValueChanged += MethodHandler(this, &Label::Text_ValueChanged);
    Font.ValueChanged += MethodHandler(this, &Label::Font_ValueChanged);
    ClientRectangle.ValueChanged += MethodHandler(this, &Label::ClientRectangle_Changed);
    }

// ----------------------------------------------------------------------------
// Label::~Label
// Destructor
// ----------------------------------------------------------------------------
//
EXPORT_C Label::~Label()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// Label::OnPaint
// Paints the label on the graphics context
// ----------------------------------------------------------------------------
//
EXPORT_C void Label::OnPaint(PaintEventArgs& aArgs)
    {
    CBitmapContext& gc = aArgs.Graphics();
    gc.SetClippingRect(ClientRectangle);

    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(BackgroundColor);
    gc.Clear(aArgs.ClipRectangle());

    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetPenColor(Color);
    gc.SetPenSize(TSize(1, 1));
    gc.UseFont(Font);
    gc.DrawText(Text, TextPosition);
    gc.DiscardFont();

    gc.CancelClippingRect();
    Control::OnPaint(aArgs);
    }

// ----------------------------------------------------------------------------
// Label::Measure
// From Control, Measure.
// ----------------------------------------------------------------------------
//
TSize Label::Measure(const TSize& aAvailableSize)
    {
    TSize preferredSize(Font->TextWidthInPixels(Text), Font->FontMaxHeight() + 1);
    preferredSize += MarginsSize();
    NumericUtils::LimitSize(preferredSize, aAvailableSize);
    PreferredSize = preferredSize;
    return preferredSize;
    }

// ----------------------------------------------------------------------------
// Label::Arrange
// Arranges the control on the screen.
// ----------------------------------------------------------------------------
//
TSize Label::Arrange(const TSize& aFinalSize)
    {
    const CFont& font = *Font;

    TInt textWidth = font.TextWidthInPixels(Text);
    TRect clientRect = ClientRectangle;

    TPoint textPosition = clientRect.iTl;
    textPosition.iX += DoAlign(TextAlignment, clientRect.Width(), textWidth);
    textPosition.iY += font.FontMaxAscent();
    TextPosition = textPosition;
    return aFinalSize;
    }

// ----------------------------------------------------------------------------
// Label::Align_ValueChanged
// Handles Align property changed.
// ----------------------------------------------------------------------------
//
void Label::TextAlign_ValueChanged(const PropertyBase<HAlignment::Align>& /*aAlign*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Label::Text_ValueChanged
// Handles Text property changed.
// ----------------------------------------------------------------------------
//
void Label::Text_ValueChanged(const PropertyBase<const TDesC&>& /*aText*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Label::Font_ValueChanged
// Handles Font property changed.
// ----------------------------------------------------------------------------
//
void Label::Font_ValueChanged(const PropertyBase<const CFont*>& /*aFont*/)
    {
    LayoutDeferred();
    }

void Label::ClientRectangle_Changed(const PropertyBase<TRect>& /*aClientRectangle*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Label::Layout
// Performs layout.
// ----------------------------------------------------------------------------
//
void Label::Layout()
    {
    Arrange(Size);
    }
