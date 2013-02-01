#include "wsclient.h"
#include "wsredrawer.h"
#include <apgwgnam.h>

// ----------------------------------------------------------------------------
// WsClient::WsClient
// Constructor.
// ----------------------------------------------------------------------------
//
WsClient::WsClient(const TUid& aAppUid)
: CActive(CActive::EPriorityStandard)
, Screen(*this, &WsClient::GetScreenDevice)
, Gc(*this, &WsClient::GetGc)
, WsSession(*this, &WsClient::GetWsSession)
, WindowGroup(*this, &WsClient::GetWindowGroup)
, iAppUid(aAppUid)
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// WsClient::~WsClient
// Destructor..
// ----------------------------------------------------------------------------
//
WsClient::~WsClient()
    {
    Deque();
    delete iGc;
    delete iScreen;
    delete iWgName;
    iGroup.Close();
    iWs.Close();
    }

// ----------------------------------------------------------------------------
// WsClient::ConstructL
// Second phase constructor.
// ----------------------------------------------------------------------------
//
void WsClient::ConstructL()
    {
    CActiveScheduler::Add(this);
    User::LeaveIfError(iWs.Connect());

    iGroup = RWindowGroup(iWs);
    User::LeaveIfError(iGroup.Construct((TInt)&iGroup, ETrue));
    iGroup.EnableScreenChangeEvents();

    iWgName = CApaWindowGroupName::NewL(iWs, (TInt)&iGroup);
    iWgName->SetAppUid(iAppUid);
    iWgName->SetWindowGroupName(iGroup);

    iScreen = new (ELeave) CWsScreenDevice(iWs);
    User::LeaveIfError(iScreen->Construct());
    User::LeaveIfError(iScreen->CreateContext(iGc));

    IssueRequest();
    }

// ----------------------------------------------------------------------------
// WsClient::Destroy
// Destroys the object.
// ----------------------------------------------------------------------------
//
void WsClient::Destroy()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// WsClient::IssueRequest
// Issues a request for window server requests.
// ----------------------------------------------------------------------------
//
void WsClient::IssueRequest()
    {
    iWs.EventReady(&iStatus);
    SetActive();
    }

// ----------------------------------------------------------------------------
// WsClient::ScreenSize
// Retrieves the screen size.
// ----------------------------------------------------------------------------
//
TSize WsClient::ScreenSize()
    {
    TPixelsAndRotation pixAndRotation;
    iScreen->GetScreenModeSizeAndRotation(iScreen->CurrentScreenMode(), pixAndRotation);
    return pixAndRotation.iPixelSize;
    }

// ----------------------------------------------------------------------------
// WsClient::DoCancel
// From CActive. Stops any asynchronous requests.
// ----------------------------------------------------------------------------
//
void WsClient::DoCancel()
    {
    iWs.EventReadyCancel();
    }

// ----------------------------------------------------------------------------
// WsClient::RunL
// From CActive, called when a window server message has been received.
// ----------------------------------------------------------------------------
//
void WsClient::RunL()
    {
    iWs.GetEvent(iWsEvent);
    switch (iWsEvent.Type())
        {
        case EEventScreenDeviceChanged:
            {
            iScreen->SetAppScreenMode(iScreen->CurrentScreenMode());
            break;
            }
        default:
            {
            break;
            }
        }
    WsEvent(iWsEvent);
    IssueRequest();
    }

// ----------------------------------------------------------------------------
// WsClient::GetScreenDevice
// Retrieves the screen device object.
// ----------------------------------------------------------------------------
//
CWsScreenDevice& WsClient::GetScreenDevice() const
    {
    return *iScreen;
    }

// ----------------------------------------------------------------------------
// WsClient::GetGc
// Retrieves the graphics context.
// ----------------------------------------------------------------------------
//
CWindowGc& WsClient::GetGc() const
    {
    return *iGc;
    }

// ----------------------------------------------------------------------------
// WsClient::GetWsSession
// Retrieves the window server session.
// ----------------------------------------------------------------------------
//
RWsSession& WsClient::GetWsSession() const
    {
    return iWs;
    }

// ----------------------------------------------------------------------------
// WsClient::GetWindowGroup
// Retrieves the window group.
// ----------------------------------------------------------------------------
//
RWindowGroup& WsClient::GetWindowGroup() const
    {
    return iGroup;
    }
