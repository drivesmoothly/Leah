// USER INCLUDES
#include "panel.h"
#include "handlermethod.h"

// ----------------------------------------------------------------------------
// Panel::Panel
// Constructor
// ----------------------------------------------------------------------------
//
EXPORT_C Panel::Panel()
: BackgroundColor(KRgbTransparent)
    {
    BackgroundColor.ValueChanged += MethodHandler(this, &Panel::BackgroundColor_Changed);
    CanFocus = ETrue;
    Enabled = ETrue;
    }

// ----------------------------------------------------------------------------
// Panel::~Panel
// Destructor.
// ----------------------------------------------------------------------------
//
EXPORT_C Panel::~Panel()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// Panel::BackgroundColor_Changed
// Handles BackgroundColor property change. Issues a redraw event.
// ----------------------------------------------------------------------------
//
EXPORT_C void Panel::BackgroundColor_Changed(const PropertyBase<TRgb>& /*aBackgroundColor*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Panel::OnPaint
// Paints the panel background on the graphics context.
// ----------------------------------------------------------------------------
//
EXPORT_C void Panel::OnPaint(PaintEventArgs& aArgs)
    {
    CBitmapContext& gc = aArgs.Graphics();
    gc.SetBrushColor(BackgroundColor);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.Clear(aArgs.ClipRectangle());

    Control::OnPaint(aArgs);
    }
