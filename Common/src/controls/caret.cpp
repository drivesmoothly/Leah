#include "caret.h"
#include "handlermethod.h"

// ----------------------------------------------------------------------------
// Caret::Caret
// Caret class constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C Caret::Caret()
: CaretWidth(2)
, BlinkInterval(750000)
, CaretColor(KRgbWhite)
, DrawCaret(EFalse)
    {
    Visible.ValueChanged += MethodHandler(this, &Caret::Visible_Changed);
    CaretWidth.ValueChanged += MethodHandler(this, &Caret::CaretWidth_Changed);
    DrawCaret.ValueChanged += MethodHandler(this, &Caret::DrawCaret_Changed);
    BlinkInterval.ValueChanged += MethodHandler(this, &Caret::BlinkInterval_Changed);
    CaretColor.ValueChanged += MethodHandler(this, &Caret::CaretColor_Changed);
    Bounds.ValueChanged += MethodHandler(this, &Caret::Bounds_Changed);

    _timer = CPeriodic::NewL(CPeriodic::EPriorityIdle);
    Visible_Changed(Visible);
    }

// ----------------------------------------------------------------------------
// Caret::~Caret
// Caret class destructor.
// ----------------------------------------------------------------------------
//
EXPORT_C Caret::~Caret()
    {
    StopBlinkTimer();
    delete _timer;
    }

// ----------------------------------------------------------------------------
// Caret::OnPaint
// From base class, draws the caret.
// ----------------------------------------------------------------------------
//
EXPORT_C void Caret::OnPaint(PaintEventArgs& aArgs)
    {
    if (DrawCaret)
        {
        CBitmapContext& gc = aArgs.Graphics();
        gc.SetPenStyle(CGraphicsContext::ESolidPen);
        gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
        gc.SetPenColor(CaretColor);
        gc.SetBrushColor(CaretColor);
        gc.DrawRect(TRect(TSize(CaretWidth, Height)));
        }
    }

// ----------------------------------------------------------------------------
// Caret::Visible_Changed
// Handles Visible property change.
// ----------------------------------------------------------------------------
//
void Caret::Visible_Changed(const PropertyBase<TBool>& aVisible)
    {
    if (aVisible)
        {
        ASSERT(!TimerRunning());
        DrawCaret = ETrue;
        StartBlinkTimer();
        }
    else
        {
        StopBlinkTimer();
        DrawCaret = EFalse;
        }
    }

// ----------------------------------------------------------------------------
// Caret::TimerTick(TAny*)
// Static callback for blinking timer.
// ----------------------------------------------------------------------------
//
TInt Caret::TimerTick(TAny* aPtr)
    {
    Caret* self = (Caret*)(aPtr);
    return self->TimerTick();
    }

// ----------------------------------------------------------------------------
// Caret::TimerTick
// Callback for blinking timer.
// ----------------------------------------------------------------------------
//
TInt Caret::TimerTick()
    {
    DrawCaret = !DrawCaret;
    return ETrue;
    }

// ----------------------------------------------------------------------------
// Caret::CaretWidth_Changed
// Handler for CaretWidth property change.
// ----------------------------------------------------------------------------
//
void Caret::CaretWidth_Changed(const PropertyBase<TInt>& /*aCaretWidth*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Caret::DrawCaret_Changed
// Handler for CaretWidth property change.
// ----------------------------------------------------------------------------
//
void Caret::DrawCaret_Changed(const PropertyBase<TBool>& /*aDrawCaret*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Caret::BlinkInterval_Changed
// Handler for BlinkInterval property change.
// ----------------------------------------------------------------------------
//
void Caret::BlinkInterval_Changed(const PropertyBase<TTimeIntervalMicroSeconds32>& /*aBlinkInterval*/)
    {
    if (TimerRunning())
        {
        StopBlinkTimer();
        StartBlinkTimer();
        }
    }

// ----------------------------------------------------------------------------
// Caret::StartBlinkTimer
// Starts the blinking timer if it's not already started.
// ----------------------------------------------------------------------------
//
void Caret::CaretColor_Changed(const PropertyBase<TRgb>& /*aCaretColor*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Caret::Bounds_Changed
// Handles the ClientRectangle property changes.
// ----------------------------------------------------------------------------
//
void Caret::Bounds_Changed(const PropertyBase<TRect>& /*aBounds*/)
    {
    if (Visible)
        {
        ASSERT(TimerRunning());
        DrawCaret = ETrue;
        StopBlinkTimer();
        StartBlinkTimer();
        }
    }

// ----------------------------------------------------------------------------
// Caret::StartBlinkTimer
// Starts the blinking timer if it's not already started.
// ----------------------------------------------------------------------------
//
void Caret::StartBlinkTimer()
    {
    if (!TimerRunning())
        {
        _timer->Start(BlinkInterval, BlinkInterval, TCallBack(&Caret::TimerTick, this));
        }
    }

// ----------------------------------------------------------------------------
// Caret::StartBlinkTimer
// Stops the blinking timer.
// ----------------------------------------------------------------------------
//
void Caret::StopBlinkTimer()
    {
    _timer->Cancel();
    }

// ----------------------------------------------------------------------------
// Caret::TimerRunning
// Checks if the timer is running.
// ----------------------------------------------------------------------------
//
TBool Caret::TimerRunning() const
    {
    return _timer->IsActive();
    }
