#include "checkbox.h"
#include "handlermethod.h"
#include "label.h"
#include "propertybind.h"
#include "image.h"
#include "application.h"
#include "fontsmanager.h"
#include "numericutils.h"
#include "imagestore.h"

// Constants
const TInt KImageTextPadSize = 5;

// ----------------------------------------------------------------------------
// CheckBox::CheckBox
// CheckBox class constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C CheckBox::CheckBox()
: Checked(EFalse)
, Text(*this, &CheckBox::GetText, &CheckBox::SetText)
, Font(*this, &CheckBox::GetFont, &CheckBox::SetFont)
, Color(*this, &CheckBox::GetColor, &CheckBox::SetColor)
    {
    _label = new (ELeave) Label();
    AddControl(_label);

    _checkedImage = new (ELeave) Image();
    _checkedImage->Align = Alignment::EHMidVMid;
    _checkedImage->SetBitmapId(ImageStore::EBitmapIdCheckBoxChecked);
    _checkedImage->Visible = Checked;
    AddControl(_checkedImage);

    _uncheckedImage = new (ELeave) Image();
    _uncheckedImage->Align = Alignment::EHMidVMid;
    _uncheckedImage->SetBitmapId(ImageStore::EBitmapIdCheckBoxUnchecked);
    _uncheckedImage->Visible = !Checked;
    AddControl(_uncheckedImage);

    Font = Application::Instance()->Fonts->NormalFont();

    Checked.ValueChanged += MethodHandler(this, &CheckBox::Checked_Changed);

    CanFocus = ETrue;
    Capture = ETrue;
    }

// ----------------------------------------------------------------------------
// CheckBox::~CheckBox
// CheckBox class destructor.
// ----------------------------------------------------------------------------
//
EXPORT_C CheckBox::~CheckBox()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// CheckBox::OnPaint
// Paints the control to the graphics context.
// ----------------------------------------------------------------------------
//
EXPORT_C void CheckBox::OnPaint(PaintEventArgs& aArgs)
    {
    CBitmapContext& gc = aArgs.Graphics();
    gc.SetClippingRect(ClientRectangle);

    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(BackgroundColor);
    gc.Clear(aArgs.ClipRectangle());

    gc.CancelClippingRect();

    Control::OnPaint(aArgs);
    }

// ----------------------------------------------------------------------------
// CheckBox::OnClick
// Handles Click event.
// ----------------------------------------------------------------------------
//
void CheckBox::OnClick()
    {
    Checked = !Checked;
    Control::OnClick();
    }

// ----------------------------------------------------------------------------
// CheckBox::Layout
// Performs layout.
// ----------------------------------------------------------------------------
//
void CheckBox::Layout()
    {
    Arrange(Size);
    }

// ----------------------------------------------------------------------------
// CheckBox::Measure
// From Control, Measure. Measures the necessary size for the control.
// ----------------------------------------------------------------------------
//
TSize CheckBox::Measure(const TSize& aAvailableSize)
    {
    const CFont& font = *Font;
    TSize imageSize = NumericUtils::BoundingSize(_checkedImage->Measure(aAvailableSize),
            _uncheckedImage->Measure(aAvailableSize));
    TSize textSize(font.TextWidthInPixels(Text), font.FontMaxHeight());
    TSize preferredSize(imageSize.iWidth + KImageTextPadSize + textSize.iWidth,
            Max(textSize.iHeight, imageSize.iHeight));
    preferredSize += MarginsSize();
    PreferredSize = preferredSize;
    return preferredSize;
    }

// ----------------------------------------------------------------------------
// CheckBox::Arrange
// Arranges the control components.
// ----------------------------------------------------------------------------
//
TSize CheckBox::Arrange(const TSize& aFinalSize)
    {
    // ASSUMPTION: Checkbox tick is always on the left
    TRect clientRect = ClientRectangle;
    TSize checkSize = NumericUtils::BoundingSize(_checkedImage->PreferredSize, _uncheckedImage->PreferredSize);
    TRect checkRect(TPoint(clientRect.iTl.iX, clientRect.iTl.iY), checkSize);
    _checkedImage->Bounds = checkRect;
    _uncheckedImage->Bounds = checkRect;
    TRect labelRect(TPoint(checkRect.iBr.iX + KImageTextPadSize, clientRect.iTl.iY), clientRect.iBr);
    labelRect.Move(0, DoAlign(VAlignment::EMid, labelRect.Height(), Font->FontMaxHeight()));
    _label->Bounds = labelRect;

    return aFinalSize;
    }

// ----------------------------------------------------------------------------
// CheckBox::Checked_Changed
// Handles Checked property changed.
// ----------------------------------------------------------------------------
//
void CheckBox::Checked_Changed(const PropertyBase<TBool>& /*aChecked*/)
    {
    _checkedImage->Visible = Checked;
    _uncheckedImage->Visible = !Checked;
    Invalidate();
    }

// ----------------------------------------------------------------------------
// CheckBox::Color_Changed
// Handles Color property change.
// ----------------------------------------------------------------------------
//
void CheckBox::Color_Changed(const PropertyBase<TRgb>& /*aColor*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// CheckBox::BackgroundColor_Changed
// Handles BackgroundColor property change.
// ----------------------------------------------------------------------------
//
void CheckBox::BackgroundColor_Changed(const PropertyBase<TRgb>& /*aBackgroundColor*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// CheckBox::GetText
// Retrieves the Text property from the label
// ----------------------------------------------------------------------------
//
const TDesC& CheckBox::GetText() const
    {
    ASSERT(_label);
    return _label->Text;
    }

// ----------------------------------------------------------------------------
// CheckBox::SetText
// Sets the Text property to the label
// ----------------------------------------------------------------------------
//
void CheckBox::SetText(const TDesC& aText)
    {
    ASSERT(_label);
    _label->Text = aText;
    }

// ----------------------------------------------------------------------------
// CheckBox::GetFont
// Retrieves the Font from the label.
// ----------------------------------------------------------------------------
//
const CFont* CheckBox::GetFont() const
    {
    ASSERT(_label);
    return _label->Font;
    }

// ----------------------------------------------------------------------------
// CheckBox::SetFont
// Sets the Font property to the label.
// ----------------------------------------------------------------------------
//
void CheckBox::SetFont(const CFont* aFont)
    {
    ASSERT(_label);
    _label->Font = aFont;
    }

// ----------------------------------------------------------------------------
// CheckBox::GetColor
// Retrieves the Color from the label.
// ----------------------------------------------------------------------------
//
TRgb CheckBox::GetColor() const
    {
    ASSERT(_label);
    return _label->Color;
    }

// ----------------------------------------------------------------------------
// CheckBox::SetColor
// Sets the Color to the label
// ----------------------------------------------------------------------------
//
void CheckBox::SetColor(TRgb aColor)
    {
    ASSERT(_label);
    _label->Color = aColor;
    }
