#include "LeahConfApplication.h"
#include "LeahConfIntroForm.h"
#include "LeahConfMainForm.h"
#include "LeahConsts.hrh"

// ----------------------------------------------------------------------------
// LeahConfApplication::LeahConfApplication
// Constructor
// ----------------------------------------------------------------------------
//
LeahConfApplication::LeahConfApplication()
: Application(TUid::Uid(K_LEAH_CONFIG_UID))
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// LeahConfApplication::~LeahConfApplication
// Destructor.
// ----------------------------------------------------------------------------
//
LeahConfApplication::~LeahConfApplication()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// LeahConfApplication::ShowMainForm
// Shows the main form.
// ----------------------------------------------------------------------------
//
void LeahConfApplication::ShowMainForm()
    {
    SetCurrentForm(iMainForm);
    }

// ----------------------------------------------------------------------------
// LeahConfApplication::ShowIntroForm
// Shows the intro form.
// ----------------------------------------------------------------------------
//
void LeahConfApplication::ShowIntroForm()
    {
    SetCurrentForm(iIntroForm);
    }

// ----------------------------------------------------------------------------
// LeahConfApplication::CreateForms
// Creates the forms.
// ----------------------------------------------------------------------------
//
void LeahConfApplication::CreateForms()
    {
    iIntroForm = new (ELeave) LeahConfIntroForm(*this);
    AddForm(iIntroForm);

    iMainForm = new (ELeave) LeahConfMainForm(*this);
    AddForm(iMainForm);

    SetCurrentForm(iIntroForm);
    }
