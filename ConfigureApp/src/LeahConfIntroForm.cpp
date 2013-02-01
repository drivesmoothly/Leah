// USER INCLUDES
#include "LeahConfApplication.h"
#include "LeahConfIntroForm.h"
#include "button.h"
#include "handlermethod.h"

// ----------------------------------------------------------------------------
// LeahConfIntroForm::LeahConfIntroForm
// Constructor.
// ----------------------------------------------------------------------------
//
LeahConfIntroForm::LeahConfIntroForm(Application& aApplication)
: Form(aApplication)
, iApplication(static_cast<LeahConfApplication*>(&aApplication))
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// LeahConfIntroForm::~LeahConfIntroForm
// Destructor.
// ----------------------------------------------------------------------------
//
LeahConfIntroForm::~LeahConfIntroForm()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// LeahConfIntroForm::Create
// Creates the child controls.
// ----------------------------------------------------------------------------
//
void LeahConfIntroForm::Create()
    {
    Form::Create();

    ButtonNext->Click += MethodHandler(this, &LeahConfIntroForm::ButtonNext_Click);
    }

// ----------------------------------------------------------------------------
// LeahConfIntroForm::OnPaint
// Paints the form on a graphics context.
// ----------------------------------------------------------------------------
//
void LeahConfIntroForm::OnPaint(PaintEventArgs& aArgs)
    {
    CBitmapContext& gc = aArgs.Graphics();

    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(TRgb(40, 40, 40));
    gc.Clear(aArgs.ClipRectangle());

    Form::OnPaint(aArgs);
    }

// ----------------------------------------------------------------------------
// LeahConfIntroForm::ButtonNext_Click
// Handles Click event from the Next button.
// ----------------------------------------------------------------------------
//
void LeahConfIntroForm::ButtonNext_Click(Control* /*aButton*/)
    {
    iApplication->ShowMainForm();
    }
