#ifndef PANEL_H_
#define PANEL_H_

// SYSTEM INCLUDES
#include <gdi.h>

// USER INCLUDES
#include "control.h"

/**
 * Defines a panel.
 * The panel is the base class for all layout classes.
 */
class Panel : public Control
    {
public: // Properties
    /// The background color
    Property<TRgb> BackgroundColor;

public: // Constructors and destructors
    /**
     * Constructor.
     */
    IMPORT_C Panel();
    /**
     * Destructor.
     */
    IMPORT_C ~Panel();

protected: // New functions
    /**
     * Handles the BackgroundColor property change.
     * Issues a redraw request.
     * @param aBackground The background property.
     */
    IMPORT_C virtual void BackgroundColor_Changed(const PropertyBase<TRgb>& aBackground);

protected: // From base class
    /**
     * From Control, OnPaint.
     * Paints the background color.
     * @param aArgs The Paint event arguments.
     */
    IMPORT_C void OnPaint(PaintEventArgs& aArgs);
    };

#endif //LAYOUT_H_
