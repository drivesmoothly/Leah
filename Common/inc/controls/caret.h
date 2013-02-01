#ifndef CARET_H_
#define CARET_H_

// SYSTEM INCLUDES
#include <gdi.h>

// USER INCLUDES
#include "control.h"

/**
 * Draws a caret to the screen.
 * When the caret is visible, it is blinking.
 */
class Caret : public Control
    {
public: // PROPERTIES
    Property<TInt> CaretWidth;
    Property<TTimeIntervalMicroSeconds32> BlinkInterval;
    Property<TRgb> CaretColor;

protected: // PROPERTIES
    Property<TBool> DrawCaret;

public: // CONSTRUCTORS AND DESTRUCTORS
    /**
     * Constructor.
     * Initializes all the properties and registers handlers to property changes.
     */
    IMPORT_C Caret();
    /**
     * Destructor.
     * Destroys internal members.
     */
    IMPORT_C ~Caret();

public: // FROM BASE CLASS
    /**
     * From Control, called to redraw the control.
     */
    IMPORT_C void OnPaint(PaintEventArgs& aArgs);

protected: // NEW FUNCTIONS
    /**
     * Handles Visible property changes. Starts or stops the caret timer.
     * @param aVisible The Visible property.
     */
    void Visible_Changed(const PropertyBase<TBool>& aVisible);
    /**
     * Callback function for timer callback.
     * @param aPtr A pointer to this.
     * @return Always returns ETrue to continue the timer.
     */
    static TInt TimerTick(TAny* aPtr);
    /**
     * Callback function for timer callback. Non-static version.
     * Switches the internal state of the DrawCaret property.
     * @return Always returns ETrue to continue the timer.
     */
    TInt TimerTick();
    /**
     * Handles CaretWidth property change.
     * Initiates a redraw if necessary.
     * @param aCaretWidth The CaretWidth property.
     */
    void CaretWidth_Changed(const PropertyBase<TInt>& aCaretWidth);
    /**
     * Handles DrawCaret property change.
     * Initiates a redraw for the caret.
     * @param aDrawCaret The DrawCaret property.
     */
    void DrawCaret_Changed(const PropertyBase<TBool>& aDrawCaret);
    /**
     * Handles the BlinkInterval property change.
     * Resets the timer to use the new blink value.
     * @param aBlinkInterval The BlinkIntervalProperty.
     */
    void BlinkInterval_Changed(const PropertyBase<TTimeIntervalMicroSeconds32>& aBlinkInterval);
    /**
     * Handles the CaretColor property change.
     * Redraws the caret to the screen.
     * @param aCaretColor The CaretColor property.
     */
    void CaretColor_Changed(const PropertyBase<TRgb>& aCaretColor);
    /**
     * Handles the ClientRectangle property change.
     * Makes the caret visible and restarts the blinking clock.
     * @param aClientRect The new client rectangle.
     */
    void Bounds_Changed(const PropertyBase<TRect>& aClientRect);

private: // NEW FUNCTIONS
    /**
     * Starts the blinking timer.
     */
    void StartBlinkTimer();
    /**
     * Stops the blinking timer.
     */
    void StopBlinkTimer();
    /**
     * Checks if the timer is running.
     * @return ETrue if running, EFalse if not.
     */
    TBool TimerRunning() const;

private: // DATA
    /// The caret timer. Allows the caret to blink.
    CPeriodic* _timer;
    };

#endif //CARET_H_
