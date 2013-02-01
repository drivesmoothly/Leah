#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include <gdi.h>
#include "control.h"
#include "align.h"

class CFont;

class TextBox : public Control
    {
public: // Properties
    PropertyDes Text;
    Property<const CFont*> Font;
    Property<TRgb> Color;
    Property<TRgb> BackgroundColor;
    Property<Alignment::Align> Align;
    Property<HAlignment::Align> HAlign;
    Property<VAlignment::Align> VAlign;
    Property<TReal> LineSpacing;

public: // Constructors and destructors
    IMPORT_C TextBox();
    IMPORT_C ~TextBox();

public: // From base class
    IMPORT_C void OnPaint(PaintEventArgs& aArgs);

protected:
    /**
     * From Control, Layout.
     */
    void Layout();
    /**
     * From Control, Measure
     * @param aAvailableSize The available size.
     * @return The necessary size.
     */
    TSize Measure(const TSize& aAvailableSize);
    /**
     * From Control, Arrange.
     * @param aFinalSize The final size given.
     * @return The actual size used.
     */
    TSize Arrange(const TSize& aFinalSize);

protected: // New functions
    void Align_Changed(const PropertyBase<Alignment::Align>& aAlign);
    void Text_Changed(const PropertyBase<const TDesC&>& aText);
    void Font_Changed(const PropertyBase<const CFont*>& aFont);
    void ClientRectangle_Changed(const PropertyBase<TRect>& aClientRect);
    void LineSpacing_Changed(const PropertyBase<TReal>& aLineSpacing);

    /**
     * Splits text to lines.
     * @param aSize The available size to split the text to.
     * @param aFont The font to use.
     * @return The size of the text.
     */
    TSize SplitTextToLines(const TSize& aSize, const CFont& aFont, const TReal& aSpacing);
    /**
     * Appends a line to the lines of text and returns the width in pixels.
     * @param aLine The line to append.
     * @param aFont The font to use.
     * @return The width in pixels.
     */
    TInt AppendLine(const TDesC& aLine, const CFont& aFont);

private: // Data
    RArray<TPoint> _linesPositions;
    RArray<TPtrC> _lines;
    };

#endif //TEXTBOX_H_
