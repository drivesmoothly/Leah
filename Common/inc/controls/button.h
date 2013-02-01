#ifndef BUTTON_H_
#define BUTTON_H_

// SYSTEM INCLUDES
#include <gdi.h>

// USER INCLUDES
#include "control.h"
#include "align.h"

// FORWARDS
class CFont;

/**
 * Button class.
 * Responsible for presenting a button in the UI.
 */
class Button : public Control
    {
public: // STATE
    enum TState
        {
        ENotPressed,
        EPressed
        };

public: // PROPERTIES
    PropertyDes Text;
    Property<const CFont*> Font;
    Property<TRgb> Color;
    Property<TRgb> BackgroundColor;
    Property<TRgb> HighlightColor;
    Property<Alignment::Align> Align;
    Property<TInt> CornerRadius;
    Property<TInt> BorderSize;
    Property<TRgb> BorderColor;
    Property<TState> State;

public: // CONSTRUCTORS AND DESTRUCTORS
    Button();
    ~Button();

public: // FROM BASE CLASS
    void OnPaint(PaintEventArgs& aArgs);
    void OnDragEnter(DragEventArgs& aArgs);
    void OnDragLeave();

protected: // From base class
    TSize Measure(const TSize& aAvailableSize);
    TSize Arrange(const TSize& aFinalSize);

protected: // NEW FUNCTIONS
    void Text_Changed(const PropertyBase<const TDesC&>& aText);
    void Font_Changed(const PropertyBase<const CFont*>& aFont);
    void Color_Changed(const PropertyBase<TRgb>& aColor);
    void BackgroundColor_Changed(const PropertyBase<TRgb>& aBackgroundColor);
    void Align_Changed(const PropertyBase<Alignment::Align>& aAlign);
    void CornerRadius_Changed(const PropertyBase<TInt>& aCornerRadius);
    void State_Changed(const PropertyBase<TState>& aState);

private: // NEW FUNCTIONS
    void Layout();

private: // DATA
    TPoint _textPosition;
    };

#endif //BUTTON_H_
