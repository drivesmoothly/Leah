#include "LeahConfMainForm.h"
#include "application.h"
#include "wsclient.h"
#include "handlermethod.h"
#include "fontsmanager.h"
#include "stringutils.h"
#include "label.h"
#include "textbox.h"
#include "button.h"
#include "editbox.h"
#include "image.h"
#include "checkbox.h"
#include "LeahConfApplication.h"

// ----------------------------------------------------------------------------
// LeahConfMainForm::LeahConfMainForm
// Constructor.
// ----------------------------------------------------------------------------
//
LeahConfMainForm::LeahConfMainForm(Application& aApplication)
: Form(aApplication)
, iApplication(static_cast<LeahConfApplication*>(&aApplication))
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// LeahConfMainForm::~LeahConfMainForm
// Destructor.
// ----------------------------------------------------------------------------
//
LeahConfMainForm::~LeahConfMainForm()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// LeahConfMainForm::Create
// Creates the form.
// ----------------------------------------------------------------------------
//
void LeahConfMainForm::Create()
    {
    Form::Create();

    ButtonExit->Click += MethodHandler(this, &LeahConfMainForm::ButtonNext_Click);
    ButtonBack->Click += MethodHandler(this, &LeahConfMainForm::ButtonBack_Click);
}

// ----------------------------------------------------------------------------
// LeahConfMainForm::OnPaint
// Paints the form on the screen.
// ----------------------------------------------------------------------------
//
void LeahConfMainForm::OnPaint(PaintEventArgs& aArgs)
    {
    CBitmapContext& gc = aArgs.Graphics();

    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(TRgb(40, 40, 40));
    gc.Clear(aArgs.ClipRectangle());

    Form::OnPaint(aArgs);
    }

// ----------------------------------------------------------------------------
// LeahConfMainForm::OnKeyPress
// Handles key events.
// ----------------------------------------------------------------------------
//
void LeahConfMainForm::OnKeyPress(KeyPressEventArgs& aArgs)
    {
    switch (aArgs.KeyChar)
        {
        case '1':
            {
            App->Stop();
            aArgs.Handled = ETrue;
            break;
            }
        default:
            {
            break;
            }
        }
    Form::OnKeyPress(aArgs);
    }

// ----------------------------------------------------------------------------
// LeahConfMainForm::ButtonNext_Click
// Handles ButtonNext click event.
// ----------------------------------------------------------------------------
//
void LeahConfMainForm::ButtonNext_Click(Control* /*aSender*/)
    {
    iApplication->Stop();
    }


// ----------------------------------------------------------------------------
// LeahConfMainForm::ButtonNext_Click
// Handles ButtonNext click event.
// ----------------------------------------------------------------------------
//
void LeahConfMainForm::ButtonBack_Click(Control* /*aSender*/)
    {
    iApplication->ShowIntroForm();
    }
