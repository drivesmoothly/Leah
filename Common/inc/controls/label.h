#ifndef LABEL_H_
#define LABEL_H_

#include <gdi.h>
#include "control.h"
#include "align.h"

class CFont;

class Label : public Control
    {
public: // Attachable properties
    /// Dependency property for Text property.
    static PropertyDes* const                   TextProperty;
    static Property<const CFont*>* const        FontProperty;
    static Property<TRgb>* const                ColorProperty;
    static Property<TRgb>* const                BackgroundColorProperty;
    static Property<HAlignment::Align>* const   TextAlignmentProperty;

public: // Properties
    PropertyDepend<const TDesC&>        Text;
    PropertyDepend<const CFont*>        Font;
    PropertyDepend<TRgb>                Color;
    PropertyDepend<TRgb>                BackgroundColor;
    PropertyDepend<HAlignment::Align>   TextAlignment;

protected: // Properties
    Property<TPoint> TextPosition;

public: // Constructors and destructors
    IMPORT_C Label();
    IMPORT_C ~Label();

public: // From base class
    IMPORT_C void OnPaint(PaintEventArgs& aArgs);
    /**
     * From Control, Measure.
     * @param aAvailableSize The available size for the control.
     * @return The preferred size.
     */
    TSize Measure(const TSize& aAvailableSize);
    /**
     * Arranges the control.
     * @param aFinalSize The final size.
     * @return The actual size used by the control.
     */
    TSize Arrange(const TSize& aFinalSize);

protected: // New functions
    void TextAlign_ValueChanged(const PropertyBase<HAlignment::Align>& aAlign);
    void Text_ValueChanged(const PropertyBase<const TDesC&>& aText);
    void Font_ValueChanged(const PropertyBase<const CFont*>& aFont);
    void ClientRectangle_Changed(const PropertyBase<TRect>& aClientRectangle);

    void Layout();
    };

#endif //LABEL_H_
