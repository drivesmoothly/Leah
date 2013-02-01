#ifndef CHECKBOX_H_
#define CHECKBOX_H_

// SYSTEM INCLUDES
#include <gdi.h>

// USER INCLUDES
#include "control.h"
#include "align.h"

// FORWARDS
class Label;
class Image;

/**
 * Draws a checkbox to the screen.
 * Checkbox can be checked and unchecked by the user.
 */
class CheckBox : public Control
    {
public: // PROPERTIES
    /// Checked
    Property<TBool> Checked;
    /// The text to display
    PropertyExt<const TDesC&, CheckBox> Text;
    /// The font to use
    PropertyExt<const CFont*, CheckBox> Font;
    /// The text color
    PropertyExt<TRgb, CheckBox> Color;
    /// The background color
    Property<TRgb> BackgroundColor;

public: // Constructors and destructors
    /**
     * Constructor.
     */
    IMPORT_C CheckBox();
    /**
     * Destructor.
     */
    IMPORT_C ~CheckBox();

public: // From base class
    /**
     * From Control, paints the control in the graphics context.
     * @param aArgs The paint arguments.
     */
    IMPORT_C void OnPaint(PaintEventArgs& aArgs);

protected: // From base class
    /**
     * From Control.
     * Handles click event.
     */
    void OnClick();
    /**
     * Performs layout.
     */
    void Layout();
    /**
     * From Control, Measure.
     * @param aAvailableSize The available size.
     * @return The preferred size.
     */
    TSize Measure(const TSize& aAvailableSize);
    /**
     * From Control, Arrange.
     * @param aFinalSize The final size.
     * @return The actual used size.
     */
    TSize Arrange(const TSize& aFinalSize);

protected: // New functions
    /**
     * Handles Checked property change.
     * @param aChecked The Checked property.
     */
    void Checked_Changed(const PropertyBase<TBool>& aChecked);
    /**
     * Handles Color property change.
     * @param aColor The Color property.
     */
    void Color_Changed(const PropertyBase<TRgb>& aColor);
    /**
     * Handles BackgroundColor property change.
     * @param aBackgroundColor The BackgroundColor property.
     */
    void BackgroundColor_Changed(const PropertyBase<TRgb>& aBackgroundColor);

protected: // Getters and setters for external properties
    /// Getter for Text property
    const TDesC& GetText() const;
    /// Setter for Text property
    void SetText(const TDesC& aText);
    /// Getter for Font property
    const CFont* GetFont() const;
    /// Setter for Font property
    void SetFont(const CFont* aFont);
    /// Getter for Color property.
    TRgb GetColor() const;
    /// Setter for Color property.
    void SetColor(TRgb aColor);

private: // Data
    /// The label
    Label* _label;
    Image* _checkedImage;
    Image* _uncheckedImage;
    };

#endif //CHECKBOX_H_
