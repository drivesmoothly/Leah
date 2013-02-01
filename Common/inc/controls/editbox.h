#ifndef EDITBOX_H_
#define EDITBOX_H_

// SYSTEM INCLUDES
#include <gdi.h>

// USER INCLUDES
#include "control.h"
#include "align.h"

// FORWARDS
class CFont;
class Caret;

/**
 * EditBox class.
 * Responsible for presenting an edit box in the UI.
 */
class EditBox : public Control
    {
protected: // TYPEDEFS
    enum TCommand
        {
        ECommandLayout
        };

public: // PROPERTIES
    PropertyDes Text;
    PropertyDes EmptyText;
    Property<const CFont*> Font;
    Property<TRgb> Color;
    Property<TRgb> EmptyColor;
    Property<TRgb> BackgroundColor;
    Property<Alignment::Align> Align;
    Property<TInt> CornerRadius;
    Property<TInt> BorderSize;
    Property<TRgb> BorderColor;
    /// The caret position as characters offset in the text.
    /// -1 means no caret was set
    Property<TInt> CaretOffset;

protected: // PROPERTIES
    /// The bounds of the text to be displayed.
    Property<TRect> TextBounds;
    /// The bounds of the empyy text to be displayed.
    Property<TRect> EmptyTextBounds;
    /// The bounds of the caret
    Property<TRect> CaretBounds;
    /// The scroll offset
    Property<TInt> ScrollOffset;

protected: // TYPEDEFS
    /// Typedef for the text drawer delegate
    typedef void (EditBox::*TextDrawerDelegate)(CBitmapContext& aGc);
    /// Typedef for the border drawer delegate
    typedef void (EditBox::*BorderDrawerDelegate)(CBitmapContext& aGc);

public: // CONSTRUCTORS AND DESTRUCTORS
    IMPORT_C EditBox();
    IMPORT_C ~EditBox();

public: // FROM BASE CLASS
    IMPORT_C void OnPaint(PaintEventArgs& aArgs);
    IMPORT_C void OnMouseDown(MouseEventArgs& aArgs);
    IMPORT_C void OnKeyPress(KeyPressEventArgs& aArgs);

protected: // NEW FUNCTIONS
    void Text_Changed(const PropertyBase<const TDesC&>& aText);
    void Font_Changed(const PropertyBase<const CFont*>& aFont);
    void Color_Changed(const PropertyBase<TRgb>& aColor);
    void BackgroundColor_Changed(const PropertyBase<TRgb>& aBackgroundColor);
    void Align_Changed(const PropertyBase<Alignment::Align>& aAlign);
    void CornerRadius_Changed(const PropertyBase<TInt>& aCornerRadius);
    void ClientRect_Changed(const PropertyBase<TRect>& aClientRect);
    void BorderSize_Changed(const PropertyBase<TInt>& aBorderSize);
    void Focused_Changed(const PropertyBase<TBool>& aFocused);
    void CaretOffset_Changed(const PropertyBase<TInt>& aCaretOffset);
    void TextBounds_Changed(const PropertyBase<TRect>& aBounds);
    void EmptyTextBounds_Changed(const PropertyBase<TRect>& aBounds);
    void CaretBounds_Changed(const PropertyBase<TRect>& aCaretBounds);
    void ScrollOffset_Changed(const PropertyBase<TInt>& aScrollOffset);

private: // NEW FUNCTIONS
    void Layout();
    void LayoutDeferred();
    void CalculateCaretBounds();
    void CalculateScrollOffset();

    /**
     * Delegate to draw the empty text.
     * @param aGc The graphics context to draw into.
     */
    void DrawEmptyText(CBitmapContext& aGc);
    /**
     * Delegate to draw the user text.
     * @param aGc The graphics context to draw into.
     */
    void DrawUserText(CBitmapContext& aGc);
    /**
     * Delegate to draw solid border.
     * @param aGc The graphics context to draw into.
     */
    void DrawSolidBorder(CBitmapContext& aGc);
    /**
     * Delegate to draw null border.
     * @param aGc The graphics context to draw into.
     */
    void DrawNullBorder(CBitmapContext& aGc);
    /**
     * Inputs a character to the edit box.
     * @param aChar The character to input.
     */
    void InputChar(const TChar& aChar);
    /**
     * Inputs a control character to the edit box.
     * @param aChar The character to input.
     */
    void InputControlChar(const TChar& aChar);

private: // DATA
    TPoint _textPosition;
    TPoint _emptyTextPosition;
    Caret* _caret;
    TextDrawerDelegate _textDrawer;
    BorderDrawerDelegate _borderDrawer;
    TInt _fontAscent;
    };

#endif //EDITBOX_H_
