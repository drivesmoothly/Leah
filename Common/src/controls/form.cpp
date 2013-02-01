#include "form.h"
#include "application.h"
#include "wsclient.h"
#include <w32std.h>
#include "handlermethod.h"
#include "backbuffer.h"

// ----------------------------------------------------------------------------
// Form::Form
// Constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C Form::Form(Application& aApplication, Form* aParent /* = NULL */)
: ParentForm(aParent)
, App(aApplication)
    {
    Focused = ETrue;
    WindowBounds = App->Ws->ScreenSize();
    }

// ----------------------------------------------------------------------------
// Form::~Form
// Destructor.
// ----------------------------------------------------------------------------
//
EXPORT_C Form::~Form()
    {
    if (iWindow)
        {
        iWindow->Destroy();
        iWindow = NULL;
        }
    }

// ----------------------------------------------------------------------------
// Form::Create
// From Form, Create. Infrastructure to create the form.
// ----------------------------------------------------------------------------
//
EXPORT_C void Form::Create()
    {
    WsClient& wsClient = App->Ws;
    RWindowTreeNode& parent = ParentForm() ? (RWindowTreeNode&)*ParentForm()->Window() : (RWindowTreeNode&)wsClient.WindowGroup();
    iWindow = new (ELeave) RWindow(wsClient.WsSession);
    User::LeaveIfError(iWindow->Construct(parent, (TUint32)this));
    iWindow->PointerFilter(EPointerFilterDrag, 0);

    WindowBounds.ValueChanged += MethodHandler(this, &Form::Form_WindowBounds_ValueChanged);
    Visible.ValueChanged += MethodHandler(this, &Form::Visible_Changed);
    Enabled = ETrue;

    iWindow->Activate();

    Control::Create();
    }

// ----------------------------------------------------------------------------
// Form::Unload
// Posts a command to unload this form.
// ----------------------------------------------------------------------------
//
void Form::Unload()
    {
    if (!CommandPosted(EUnload))
        {
        PostCommandL(EUnload);
        }
    }

// ----------------------------------------------------------------------------
// Form::DoUnload
// Unloads a form
// ----------------------------------------------------------------------------
//
EXPORT_C void Form::DoUnload()
    {
    FocusedChild = NULL;
    MouseOriginatingControl = NULL;
    MouseDragSource = NULL;
    iControls.ResetAndDestroy();
    WindowBounds.ValueChanged -= MethodHandler(this, &Form::Form_WindowBounds_ValueChanged);
    iWindow->Destroy();
    iWindow = NULL;
    }

// ----------------------------------------------------------------------------
// Form::GetScreen
// Infrastructure, retrieves the screen device for the application.
// ----------------------------------------------------------------------------
//
EXPORT_C CWsScreenDevice& Form::GetScreen() const
    {
    return App().Ws().Screen;
    }

// ----------------------------------------------------------------------------
// Form::GetApplication
// Infrastructure, retrieves the Application instance.
// ----------------------------------------------------------------------------
//
EXPORT_C Application& Form::GetApplication() const
    {
    return App;
    }

// ----------------------------------------------------------------------------
// Form::Measure
// From Control, Measure. Measures the necessary size for the child controls.
// ----------------------------------------------------------------------------
//
EXPORT_C TSize Form::Measure(const TSize& aAvailableSize)
    {
    const RControlsArray& childControls = Controls;
    TSize measuredSize(0, 0);
    TInt controlsCount = childControls.Count();
    for (TInt i = 0; i < controlsCount; ++i)
        {
        TSize childSize = childControls[i]->Measure(aAvailableSize);
        measuredSize.iWidth = Max(measuredSize.iWidth, childSize.iWidth);
        measuredSize.iHeight = Max(measuredSize.iHeight, childSize.iHeight);
        }
    return measuredSize;
    }

// ----------------------------------------------------------------------------
// Form::Arrange
// From Control, Arrange. Arranges the child controls.
// ----------------------------------------------------------------------------
//
EXPORT_C TSize Form::Arrange(const TSize& aFinalSize)
    {
    const RControlsArray& childControls = Controls;
    TInt controlsCount = childControls.Count();
    for (TInt i = 0; i < controlsCount; ++i)
        {
        childControls[i]->Bounds = aFinalSize;
        }
    return aFinalSize;
    }

// ----------------------------------------------------------------------------
// Form::Layout
// Performs layout.
// ----------------------------------------------------------------------------
//
EXPORT_C void Form::Layout()
    {
    Arrange(Size);
    Control::Layout();
    }

// ----------------------------------------------------------------------------
// Form::AsyncHandleCommandL
// Handles asynchronous commands
// ----------------------------------------------------------------------------
//
void Form::AsyncHandleCommandL(const TInt& aCommand)
    {
    switch (aCommand)
        {
        case EUnload:
            {
            DoUnload();
            break;
            }
        default:
            {
            Control::AsyncHandleCommandL(aCommand);
            }
        }
    }

EXPORT_C void Form::RaiseMouseEvent(Control* aSender, MouseEventArgs& aArgs)
    {
    aArgs.SetOriginatingControl(MouseOriginatingControl);
    aArgs.SetOriginatingLocation(MouseOriginatingLocation);
    aArgs.SetDragSource(MouseDragSource);
    aArgs.SetDragOver(MouseDragOver);

    if (aArgs.OriginatingControl() && aArgs.OriginatingControl()->Capture())
        {
        aArgs.OriginatingControl()->RaiseMouseEvent(aSender, aArgs);
        }
    else
        {
        Control::RaiseMouseEvent(aSender, aArgs);
        }

    MouseOriginatingControl = aArgs.OriginatingControl();
    MouseOriginatingLocation = aArgs.OriginatingLocation();
    MouseDragSource = aArgs.DragSource();
    MouseDragOver = aArgs.DragOver();
    }

void Form::Form_WindowBounds_ValueChanged(const PropertyBase<TRect>& aBounds)
    {
    ASSERT(iWindow);
    TRect bounds(aBounds);
    iWindow->SetExtent(bounds.iTl, bounds.Size());
    }

// ----------------------------------------------------------------------------
// Form::Visible_Changed
// Handles Visible property change event
// ----------------------------------------------------------------------------
//
void Form::Visible_Changed(const PropertyBase<TBool>& aVisible)
    {
    iWindow->SetVisible(aVisible);
    }
