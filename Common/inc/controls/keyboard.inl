
#include "handlermethod.h"
#include "grid.h"
#include "button.h"

// ----------------------------------------------------------------------------
// Keyboard::CreateKey
// Creates a new key button.
// ----------------------------------------------------------------------------
//
Button* Keyboard::CreateKey(const TDesC& aText, Grid& aGrid, TInt aGridColumn,
        TBool aSpecialColor, TBool aSetDragHandlers)
    {
    Button* key = new (ELeave) Button();
    aGrid.AddControl( key );
    key->Create();
    key->Text = aText;
    key->Name = aText;
    key->SetValue( &Grid::Column, aGridColumn );
    key->Margin = TRect(1, 1, 1, 1);
    key->HorizontalAlignment = HAlignment::EStretch;
    key->Align = Alignment::EHMidVMid;
    key->BackgroundColor = aSpecialColor ? SpecialKeyColor : NormalKeyColor;
    if (aSetDragHandlers)
        {
        SetButtonDragHandlers(*key);
        }
    return key;
    }

// ----------------------------------------------------------------------------
// Keyboard::SetButtonDragHandlers
// Sets the drag handlers for a given button.
// ----------------------------------------------------------------------------
//
void Keyboard::SetButtonDragHandlers(Button& aButton)
    {
    aButton.DragEnter += MethodHandler(this, &Keyboard::Button_DragEnter);
    aButton.DragLeave += MethodHandler(this, &Keyboard::Button_DragLeave);
    }

// ----------------------------------------------------------------------------
// Keyboard::GetPopupLocation
// Calculates the popup location for a given button
// ----------------------------------------------------------------------------
//
TPoint Keyboard::GetPopupLocation(Button& aButton)
    {
    TSize popupKeySize = popupKey->Size;
    TPoint popupLocation = PointToClient(aButton.PointToScreen(TPoint(0, 0)));
    popupLocation.iY -= (popupKeySize.iHeight + 15);
    popupLocation.iX -= Max(0, popupKeySize.iWidth + popupLocation.iX - Width);
    return popupLocation;
    }
