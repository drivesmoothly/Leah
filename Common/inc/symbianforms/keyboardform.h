#ifndef KEYBOARDFORM_H_
#define KEYBOARDFORM_H_

// USER INCLUDES
#include "form.h"
#include "layoutforwards.h"
#include "controlsforwards.h"

/**
 * Keyboard form that displays the keyboard.
 */
class KeyboardForm : public Form
    {
public: // Constructors and destructor
    /**
     * Constructor. Initializes the Keyboard form.
     * @param aApplication The application to register the form to.
     */
    KeyboardForm(Application& aApplication);
    /**
     * Destructor.
     */
    ~KeyboardForm();

public: // From base classes
    /**
     * From Form, Create.
     * Creates the child controls.
     */
    void Create();
    /**
     * From Control, Measure. Measures the necessary size out of a given maximum size.
     * @param aAvailableSize The maximum available size.
     * @return The available size.
     */
    TSize Measure(const TSize& aAvailableSize);

protected: // From base class
    /**
     * From Form, OnPaint.
     * Performs drawing in the given graphics context.
     * @param aArgs The paint event args.
     */
    void OnPaint(PaintEventArgs& aArgs);
    /**
     * From Form, OnKeyPress.
     * @param aArgs The key event arguments.
     */
    void OnKeyPress(KeyPressEventArgs& aArgs);

protected: // New functions
    /**
     * From Form, Form_WindowBounds_ValueChanged.
     * @param aBounds
     */
    void Form_WindowBounds_ValueChanged(const PropertyBase<TRect>& aBounds);
    /**
     * Handles the Size property change event.
     * Positions the keyboard on the screen or off the screen, depending the Visible property.
     * @param aSize The Size property.
     */
    void Size_Changed(const PropertyBase<TSize>& aSize);
    /**
     * Handles the Visible property change event.
     * @param aVisible The Visible property.
     */
    void Visible_Changed(const PropertyBase<TBool>& aVisible);

#include "KeyboardForm.xml.h"
    };

#endif //KEYBOARDFORM_H_
