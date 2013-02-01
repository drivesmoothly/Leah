#include "keyboardform.h"
#include "handlermethod.h"

// ----------------------------------------------------------------------------
// KeyboardForm::KeyboardForm
// Constructor.
// ----------------------------------------------------------------------------
//
KeyboardForm::KeyboardForm(Application& aApplication)
: Form(aApplication)
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// KeyboardForm::~KeyboardForm
// Destructor.
// ----------------------------------------------------------------------------
//
KeyboardForm::~KeyboardForm()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// KeyboardForm::Create
// Creates the form.
// ----------------------------------------------------------------------------
//
void KeyboardForm::Create()
    {
    Form::Create();

    Size.ValueChanged += MethodHandler(this, &KeyboardForm::Size_Changed);
    Visible.ValueChanged += MethodHandler(this, &KeyboardForm::Visible_Changed);

    Size = Measure(GetScreen().SizeInPixels());
    }

// ----------------------------------------------------------------------------
// KeyboardForm::Measure
// Measures the necessary size out of a maximum available size.
// ----------------------------------------------------------------------------
//
TSize KeyboardForm::Measure(const TSize& aAvailableSize)
    {
    return Form::Measure(aAvailableSize);
    }

// ----------------------------------------------------------------------------
// KeyboardForm::OnPaint
// Paints the form on the graphics context.
// ----------------------------------------------------------------------------
//
void KeyboardForm::OnPaint(PaintEventArgs& aArgs)
    {
    Form::OnPaint(aArgs);
    }

// ----------------------------------------------------------------------------
// KeyboardForm::OnKeyPress
// Handles the KeyPress event.
// ----------------------------------------------------------------------------
//
void KeyboardForm::OnKeyPress(KeyPressEventArgs& aArgs)
    {
    Form::OnKeyPress(aArgs);
    }

// ----------------------------------------------------------------------------
// KeyboardForm::Form_WindowBounds_ValueChanged
// Handles the Size property change event.
// ----------------------------------------------------------------------------
//
void KeyboardForm::Form_WindowBounds_ValueChanged(const PropertyBase<TRect>& aBounds)
    {
    Form::Form_WindowBounds_ValueChanged(aBounds);
//
//    TSize boundsSize = aBounds().Size();
//    Size = boundsSize;
//    Location = DoAlign(Alignment::EHMidVBottom, boundsSize, Measure(boundsSize));
    }

// ----------------------------------------------------------------------------
// KeyboardForm::Size_Changed
// Handles the Size property change event.
// ----------------------------------------------------------------------------
//
void KeyboardForm::Size_Changed(const PropertyBase<TSize>& aSize)
    {
    //Location = (GetScreen().SizeInPixels() - aSize).AsPoint();
    }

// ----------------------------------------------------------------------------
// KeyboardForm::Visible_Changed
// Handles the Visible property change event.
// ----------------------------------------------------------------------------
//
void KeyboardForm::Visible_Changed(const PropertyBase<TBool>& /*aVisible*/)
    {

    }
