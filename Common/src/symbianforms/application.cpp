// USER INCLUDES
#include "application.h"
#include "wsclient.h"
#include "wsredrawer.h"
#include "form.h"
#include "handlermethod.h"
#include "fontsmanager.h"
#include "defaultpropertystore.h"
#include "imagestore.h"
#include "keyboardform.h"

// SYSTEM INCLUDES
#include <akndef.h>

// Singleton instance
Application* Application::iInstance = NULL;

// ----------------------------------------------------------------------------
// Application::~Application
// Destructor.
// ----------------------------------------------------------------------------
//
Application::~Application()
    {
    iForms.ResetAndDestroy();

    delete iKeyboardForm;
    iKeyboardForm = NULL;

    delete iWsRedrawer;
    iWsRedrawer = NULL;

    delete iFontsManager;
    iFontsManager = NULL;

    delete iWsClient;
    iWsClient = NULL;

    ImageStore::Close();

    RFbsSession::Disconnect();
    iWsSession.Close();
    iFsSession.Close();

    delete iWait;
    iWait = NULL;

    DefaultPropertyStore::Close();
    }

// ----------------------------------------------------------------------------
// Application::Instance
// Retrieves the singleton instance.
// ----------------------------------------------------------------------------
//
Application* Application::Instance()
    {
    ASSERT(iInstance);
    return iInstance;
    }

// ----------------------------------------------------------------------------
// Application::Application
// Constructor.
// ----------------------------------------------------------------------------
//
Application::Application(const TUid& aUid)
: Ws(*this, &Application::GetWsClient)
, Fonts(*this, &Application::GetFontsManager)
, iAppUid(aUid)
    {
    iInstance = this;
    iForms.ResetAndDestroy();
    iWait = new (ELeave) CActiveSchedulerWait();
    }

// ----------------------------------------------------------------------------
// Application::ConstructL
// Second phase constructor.
// ----------------------------------------------------------------------------
//
void Application::ConstructL()
    {
    User::LeaveIfError(iFsSession.Connect());
    User::LeaveIfError(iWsSession.Connect(iFsSession));
    User::LeaveIfError(RFbsSession::Connect(iFsSession));

    iWsClient = new (ELeave) WsClient(iAppUid);
    iWsClient->WsEvent += MethodHandler(this, &Application::WsClient_WsEvent);
    iWsClient->ConstructL();

    iFontsManager = new (ELeave) FontsManager(Ws().Screen);
    ImageStore::Initialize();

    CreateForms();
    CreateKeyboardForm();

    iWsRedrawer = new (ELeave) WsRedrawer();
    iWsRedrawer->ConstructL(iWsClient);
    }

// ----------------------------------------------------------------------------
// Application::ThreadFunction
// Static thread function that starts the application.
// ----------------------------------------------------------------------------
//
void Application::ThreadFunction(Application* (*aFactory)())
    {
    CActiveScheduler* activeScheduler = new (ELeave) CActiveScheduler();
    CleanupStack::PushL(activeScheduler);

    CActiveScheduler::Install(activeScheduler);

    Application* self = (*aFactory)();
    CleanupStack::PushL(self);
    self->ConstructL();
    self->Start();

    CleanupStack::PopAndDestroy(2, activeScheduler);
    REComSession::FinalClose();
    }

// ----------------------------------------------------------------------------
// Application::Stop
// Asynchronously stops the application.
// ----------------------------------------------------------------------------
//
void Application::Stop()
    {
    iWait->AsyncStop();
    }

// ----------------------------------------------------------------------------
// Application::Start
// Starts the waiting loop for the application.
// ----------------------------------------------------------------------------
//
void Application::Start()
    {
    iWait->Start();
    }

// ----------------------------------------------------------------------------
// Application::CreateKeyboardForm
// Creates the keyboard form.
// ----------------------------------------------------------------------------
//
void Application::CreateKeyboardForm()
    {
    iKeyboardForm = new (ELeave) KeyboardForm(*this);
    iKeyboardForm->Create();
    iKeyboardForm->Visible = ETrue;
    }

// ----------------------------------------------------------------------------
// Application::CreateForms
// Virtual function that creates the custom forms.
// ----------------------------------------------------------------------------
//
void Application::CreateForms()
    {
    // No implementation required.
    // Implemented only to allow applications to not override this function.
    }

// ----------------------------------------------------------------------------
// Application::AddForm
// Adds a form.
// ----------------------------------------------------------------------------
//
void Application::AddForm(Form* aForm)
    {
    iForms.AppendL(aForm);
    if (NULL == iCurrentForm)
        {
        SetCurrentForm(aForm);
        }
    }

// ----------------------------------------------------------------------------
// Application::RemoveForm
// Removes a form.
// ----------------------------------------------------------------------------
//
void Application::RemoveForm(Form* aForm)
    {
    TInt pos = iForms.Find(aForm);
    if (pos != KErrNotFound)
        {
        iForms.Remove(pos);
        delete aForm;
        }
    }

// ----------------------------------------------------------------------------
// Application::SetCurrentForm
// Changes the current form.
// ----------------------------------------------------------------------------
//
void Application::SetCurrentForm(Form* aForm)
    {
    if (aForm == iCurrentForm)
        {
        return;
        }

    if (aForm)
        {
        aForm->Create();
        aForm->Window->SetOrdinalPosition(0);
        }
    if (iCurrentForm)
        {
        iCurrentForm->Unload();
        }
    iCurrentForm = aForm;
    }

// ----------------------------------------------------------------------------
// Application::CurrentForm
// Retrieves the current form.
// ----------------------------------------------------------------------------
//
Form* Application::CurrentForm() const
    {
    return iCurrentForm;
    }

// ----------------------------------------------------------------------------
// Application::GetWsClient
// Retrieves the window server client object.
// ----------------------------------------------------------------------------
//
WsClient& Application::GetWsClient() const
    {
    return *iWsClient;
    }

// ----------------------------------------------------------------------------
// Application::GetFontsManager
// Retrieves the fonts manager.
// ----------------------------------------------------------------------------
//
FontsManager& Application::GetFontsManager() const
    {
    return *iFontsManager;
    }

// ----------------------------------------------------------------------------
// Application::WsClient_WsEvent
// Handler for the WsEvent event from the window server client.
// ----------------------------------------------------------------------------
//
void Application::WsClient_WsEvent(TWsEvent& aEvent)
    {
    TInt eventType = aEvent.Type();
    Form* handlingForm = iCurrentForm;
    if (iKeyboardForm->Visible)
        handlingForm = iKeyboardForm;
    switch (eventType)
        {
        case EEventNull:
            break;
        case EEventKeyDown:
        case EEventKey:
        case EEventKeyUp:
            {
            if (NULL != handlingForm)
                {
                TKeyEvent& keyEvent = *aEvent.Key();
                KeyEventArgs args(keyEvent.iCode, keyEvent.iScanCode, keyEvent.iModifiers, eventType);
                handlingForm->RaiseKeyEvent(handlingForm, args);
                }
            break;
            }
        case EEventPointer:
            {
            Form* form = (Form*)(aEvent.Handle());
            ASSERT(form);
            TPointerEvent& pointerEvent = *aEvent.Pointer();
            MouseEventArgs args(pointerEvent.iType, pointerEvent.iPosition);
            form->RaiseMouseEvent(form, args);
            break;
            }
        case KAknShutOrHideApp:
            {
            Stop();
            break;
            }
        case EEventScreenDeviceChanged:
            {
            SetFormsSize(Ws->ScreenSize());
            break;
            }
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// Application::SetFormsSize
// Sets a new size for all the forms.
// ----------------------------------------------------------------------------
//
void Application::SetFormsSize(const TSize& aSize)
    {
    for (TInt i = 0; i < iForms.Count(); ++i)
        {
        ASSERT(iForms[i]);
        iForms[i]->WindowBounds = TRect(iForms[i]->Location, aSize);
        }
    iKeyboardForm->WindowBounds = TRect(iKeyboardForm->Location, aSize);
    }
