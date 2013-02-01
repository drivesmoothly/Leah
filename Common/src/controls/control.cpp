// USER INCLUDES
#include "control.h"
#include "propertybind.h"
#include "propertyadapters.h"
#include "backbuffer.h"
#include "debug.h"

/// Dependency properties definition
Property<TSize>* const Control::SizeProperty = NULL;
Property<TInt>* const Control::WidthProperty = NULL;
Property<TInt>* const Control::HeightProperty = NULL;
Property<TRect>* const Control::MarginProperty = NULL;
Property<TBool>* const Control::VisibleProperty = NULL;

// ----------------------------------------------------------------------------
// Control::Control
// Constructor.
// ----------------------------------------------------------------------------
//
Control::Control()
: HorizontalAlignment(HAlignment::ELeft)
, VerticalAlignment(VAlignment::ETop)
, Controls(*this, &Control::GetControlsArray)
, Window(*this, &Control::GetWindow)
, Screen(*this, &Control::GetScreen)
, App(*this, &Control::GetApplication)
, CanFocus(EFalse)
, Enabled(EFalse)
, Visible(ETrue)
, IsInvalidated(ETrue)
, InvalidatedRect(TRect())
    {
    BindTwoWayAdapt(Bounds, Top, &PropertyAdapters::FromRectToTop, &PropertyAdapters::FromTopToRect);
    BindTwoWayAdapt(Bounds, Left, &PropertyAdapters::FromRectToLeft, &PropertyAdapters::FromLeftToRect);
    BindTwoWayAdapt(Bounds, Bottom, &PropertyAdapters::FromRectToBottom, &PropertyAdapters::FromBottomToRect);
    BindTwoWayAdapt(Bounds, Right, &PropertyAdapters::FromRectToRight, &PropertyAdapters::FromRightToRect);
    BindTwoWayAdapt(Bounds, Location, &PropertyAdapters::FromRectToLocation, &PropertyAdapters::FromLocationToRect);
    BindTwoWayAdapt(Bounds, Size, &PropertyAdapters::FromRectToSize, &PropertyAdapters::FromSizeToRect);
    BindTwoWayAdapt(Bounds, Width, &PropertyAdapters::FromRectToWidth, &PropertyAdapters::FromWidthToRect);
    BindTwoWayAdapt(Bounds, Height, &PropertyAdapters::FromRectToHeight, &PropertyAdapters::FromHeightToRect);
    BindTwoWayAdapt(Bounds, BottomRight, &PropertyAdapters::FromRectToBottomRight, &PropertyAdapters::FromBottomRightToRect);

    BindTwoWayAdapt(ClientRectangle, ClientSize, &PropertyAdapters::FromRectToSize, &PropertyAdapters::FromSizeToRect);

    DoubleBuffered.ValueChanged += MethodHandler(this, &Control::DoubleBuffered_ValueChanged);
    Focused.ValueChanged += MethodHandler(this, &Control::Focused_ValueChanged);
    Margin.ValueChanged += MethodHandler(this, &Control::Margin_Changed);
    Visible.ValueChanged += MethodHandler(this, &Control::Visible_Changed);
    Size.ValueChanged += MethodHandler(this, &Control::Size_Changed);
    }

// ----------------------------------------------------------------------------
// Control::~Control
// Destructor.
// ----------------------------------------------------------------------------
//
Control::~Control()
    {
    iControls.ResetAndDestroy();
    delete iBackBuffer;
    iBackBuffer = NULL;
    }

// ----------------------------------------------------------------------------
// Control::Create
// Performs creation operations for the control.
// ----------------------------------------------------------------------------
//
void Control::Create()
    {
    InitFromXml();
    }

// ----------------------------------------------------------------------------
// Control::BringToFront
// Brings the control to front.
// ----------------------------------------------------------------------------
//
void Control::BringToFront()
    {
    ASSERT(NULL != Parent());

    Control* parent = Parent;
    RControlsArray& parentControls = parent->iControls;

    TInt myPos = parentControls.Find(this);
    ASSERT(KErrNotFound != myPos);
    if (myPos < (parentControls.Count() - 1))
        {
        parentControls.Remove(myPos);
        parentControls.AppendL(this);
        }
    }

// ----------------------------------------------------------------------------
// Control::Contains
// Checks if this control contains the given control.
// ----------------------------------------------------------------------------
//
TBool Control::Contains(Control* aControl) const
    {
    return (iControls.Find(aControl) != KErrNotFound);
    }

// ----------------------------------------------------------------------------
// Control::Focus
// Focuses the control.
// ----------------------------------------------------------------------------
//
TBool Control::Focus()
    {
    if (Focused())
        return ETrue;
    else if (GetTopLevel())
        {
        Focused = ETrue;
        return ETrue;
        }
    else if (Parent()->Focus())
        {
        return Parent()->FocusChild(this);
        }
    else
        {
        return EFalse;
        }
    }

// ----------------------------------------------------------------------------
// Control::GetChildAtPoint
// Retrieves the child control at a given position.
// ----------------------------------------------------------------------------
//
Control* Control::GetChildAtPoint(const TPoint& aPoint)
    {
    for (TInt i = iControls.Count() - 1; i >= 0; --i)
        {
        Control* child = iControls[i];
        if (child->Bounds().Contains(aPoint) && child->Visible && child->Enabled)
            {
            return child;
            }
        }
    return NULL;
    }

// ----------------------------------------------------------------------------
// Control::GetFocusingChildAtPointRecursive
// Retrieves the child at a given point in a recursive way. That is, the
// deepest child at the given position.
// ----------------------------------------------------------------------------
//
Control* Control::GetFocusingChildAtPointRecursive(const TPoint& aPoint)
    {
    for (TInt i = iControls.Count() - 1; i >= 0; --i)
        {
        Control* child = iControls[i];
        if (child->Bounds().Contains(aPoint) && child->Visible && child->Enabled && child->CanFocus)
            {
            TPoint point = aPoint - child->Location;
            Control* result = child->GetFocusingChildAtPointRecursive(point);
            return result ? result : child;
            }
        }
    return NULL;
    }

// ----------------------------------------------------------------------------
// Control::GetContainerControl
// Retrieves the parent control.
// ----------------------------------------------------------------------------
//
Control* Control::GetContainerControl()
    {
    return Parent();
    }

// ----------------------------------------------------------------------------
// Control::GetNextControl
// Retrieves the next child control after or before the given control.
// ----------------------------------------------------------------------------
//
Control* Control::GetNextControl(Control* aControl, TBool aForward)
    {
    TInt position = iControls.Find(aControl);
    if (KErrNotFound != position)
        {
        if (aForward && (position > 0))
            {
            return iControls[position - 1];
            }
        else if (!aForward && (position < iControls.Count() - 1))
            {
            return iControls[position + 1];
            }
        else
            return NULL;
        }
    return NULL;
    }

// ----------------------------------------------------------------------------
// Control::GetPreferredSize
// Retrieves the preferred size of the control.
// ----------------------------------------------------------------------------
//
TSize Control::GetPreferredSize(const TSize& /*aProposedSize*/)
    {
    return TSize(0, 0);
    }

// ----------------------------------------------------------------------------
// Control::GetTopLevel
// Checks if this control is the top level control.
// ----------------------------------------------------------------------------
//
TBool Control::GetTopLevel() const
    {
    return Parent() == NULL;
    }

// ----------------------------------------------------------------------------
// Control::TopLevelControl
// Retrieves the top level control.
// ----------------------------------------------------------------------------
//
const Control* Control::TopLevelControl() const
    {
    const Control* topLevelControl = this;
    while (topLevelControl->Parent)
        {
        topLevelControl = topLevelControl->Parent;
        }
    return topLevelControl;
    }

// ----------------------------------------------------------------------------
// Control::Hide
// Hides the control. Sets the Visible property to false.
// ----------------------------------------------------------------------------
//
void Control::Hide()
    {
    Visible = EFalse;
    }

// ----------------------------------------------------------------------------
// Control::Redraw
// Issues a redraw sequence without invalidating.
// ----------------------------------------------------------------------------
//
void Control::Redraw()
    {
    InvalidateWindow(RectangleToScreen(TRect(Size)));
    }

// ----------------------------------------------------------------------------
// Control::Invalidate
// Invalidates the control and requests a redraw.
// ----------------------------------------------------------------------------
//
void Control::Invalidate()
    {
    if (!Enabled)
        {
        return;
        }
    InvalidateControl(TRect(Size));
    InvalidateParents();
    }

// ----------------------------------------------------------------------------
// Control::Invalidate
// Invalidates a part of the control.
// ----------------------------------------------------------------------------
//
void Control::Invalidate(const TRect& aRect)
    {
    if (!Enabled)
        {
        return;
        }
    InvalidateControl(aRect);
    InvalidateParents();
    }

// ----------------------------------------------------------------------------
// Control::InvokeGotFocus
// Invokes the GotFocus event for a given control.
// ----------------------------------------------------------------------------
//
void Control::InvokeGotFocus(Control* aControl)
    {
    aControl->OnGotFocus();
    }

// ----------------------------------------------------------------------------
// Control::InvokeLostFocus
// Invokes the LostFocus event for a given control.
// ----------------------------------------------------------------------------
//
void Control::InvokeLostFocus(Control* aControl)
    {
    aControl->OnLostFocus();
    }

// ----------------------------------------------------------------------------
// Control::InvokeClick
// Invokes the Click event for a given control.
// ----------------------------------------------------------------------------
//
void Control::InvokeClick(Control* aControl)
    {
    aControl->OnClick();
    }

// ----------------------------------------------------------------------------
// Control::InvokePaint
// Invokes the Paint event for a given control.
// ----------------------------------------------------------------------------
//
void Control::InvokePaint(Control* aControl, PaintEventArgs& aArgs)
    {
    aControl->OnPaint(aArgs);
    }

// ----------------------------------------------------------------------------
// Control::PointToClient
// Transforms the given point from screen to client coordinates.
// ----------------------------------------------------------------------------
//
TPoint Control::PointToClient(const TPoint& aPoint)
    {
    return aPoint - PositionToScreen();
    }

// ----------------------------------------------------------------------------
// Control::PointToScreen
// Transforms the given point from client to screen coordinates.
// ----------------------------------------------------------------------------
//
TPoint Control::PointToScreen(const TPoint& aPoint)
    {
    return aPoint + PositionToScreen();
    }

// ----------------------------------------------------------------------------
// Control::RectangleToClient
// Transfors a rectangle from screen to client coordinates.
// ----------------------------------------------------------------------------
//
TRect Control::RectangleToClient(const TRect& aRect)
    {
    TPoint positionToScreen = PositionToScreen();

    TRect rectToClient(positionToScreen, Size);
    rectToClient.Intersection(aRect);
    rectToClient.Move(-positionToScreen);
    return rectToClient;
    }

// ----------------------------------------------------------------------------
// Control::RectangleToScreen
// Transforms a rectangle from client to screen coordinates.
// ----------------------------------------------------------------------------
//
TRect Control::RectangleToScreen(const TRect& aRect)
    {
    TPoint positionToScreen = PositionToScreen();
    TRect rectToScreen(aRect);
    rectToScreen.Move(positionToScreen);
    return rectToScreen;
    }

// ----------------------------------------------------------------------------
// Control::Refresh
// Requests a redraw of the control.
// ----------------------------------------------------------------------------
//
void Control::Refresh()
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Control::SendToBack
// Sends the control back in the parent's controls order.
// ----------------------------------------------------------------------------
//
void Control::SendToBack()
    {
    ASSERT(NULL != Parent());

    Control* parent = Parent;
    RControlsArray& parentControls = parent->iControls;

    TInt myPos = parentControls.Find(this);
    ASSERT(KErrNotFound != myPos);
    if (myPos > 0)
        {
        parentControls.Remove(myPos);
        parentControls.Insert(this, 0);
        }
    }

// ----------------------------------------------------------------------------
// Control::Show
// Makes the control visible.
// ----------------------------------------------------------------------------
//
void Control::Show()
    {
    Visible = ETrue;
    }

// ----------------------------------------------------------------------------
// Control::AddControl
// Adds a control as a child control.
// ----------------------------------------------------------------------------
//
void Control::AddControl(Control* aControl)
    {
    ASSERT(aControl);
    TInt findPos = iControls.Find(aControl);
    if (KErrNotFound == findPos)
        {
        iControls.AppendL(aControl);
        aControl->Parent = this;
        aControl->Enabled = ETrue;
        aControl->RequestFocus += MethodHandler(this, &Control::Child_RequestFocus);
        OnControlAdded(aControl);
        LayoutDeferred();
        }
    }

// ----------------------------------------------------------------------------
// Control::RemoveControl
// Removes a control from this control's children list.
// ----------------------------------------------------------------------------
//
void Control::RemoveControl(Control* aControl)
    {
    TInt findPos = iControls.Find(aControl);
    if (KErrNotFound != findPos)
        {
        iControls.Remove(findPos);
        aControl->Parent = NULL;
        OnControlRemoved(aControl);
        LayoutDeferred();
        }
    }

// ----------------------------------------------------------------------------
// Control::PositionToScreen
// Retrieves this controls's position in screen coordinates.
// ----------------------------------------------------------------------------
//
TPoint Control::PositionToScreen() const
    {
    TPoint position = Location;
    Control* ancestor = Parent;
    while (ancestor)
        {
        position += ancestor->Location;
        ancestor = ancestor->Parent;
        }
    return position;
    }

// ----------------------------------------------------------------------------
// Control::PositionToDrawContext
// Calculates the position relative to the draw context.
// ----------------------------------------------------------------------------
//
TPoint Control::PositionToDrawContext() const
    {
    TPoint position = Location;
    Control* ancestor = Parent;
    while (ancestor && !ancestor->DoubleBuffered)
        {
        position += ancestor->Location;
        ancestor = ancestor->Parent;
        }
    return position;
    }

// ----------------------------------------------------------------------------
// Control::RaisePaintEvent
// Infrastructure. Raises the required paint events and draws the controls
// in the graphics context.
// ----------------------------------------------------------------------------
//
void Control::RaisePaintEvent(Control* /*aSender*/, PaintEventArgs& aArgs)
    {
    if (!Visible)
        {
        return;
        }
    // Obtain coordinates in client space
    TRect clientRect = aArgs.ClipRectangle();
    clientRect.Move(-Location());

    // Calculate the repaint rect
    TRect repaintRect = clientRect;
    repaintRect.Intersection(TRect(Size));

    aArgs.Graphics().SetOrigin(PositionToDrawContext());
    // Implement double buffer paint policy
    if (DoubleBuffered)
        {
        if (IsInvalidated)
            {
            TRect invalidatedRect = repaintRect;
            invalidatedRect.Intersection(InvalidatedRect);
            CBitmapContext& bufferGc = *iBackBuffer->Gc;
            bufferGc.SetOrigin(TPoint(0, 0));
            bufferGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
            bufferGc.SetBrushColor(TRgb(0, 0, 0, 0));
            bufferGc.SetPenStyle(CGraphicsContext::ENullPen);
            bufferGc.Clear(invalidatedRect);
            PaintEventArgs args(*iBackBuffer->Gc, invalidatedRect);
            OnPaint(args);
            DispatchPaint(args);
            }
        aArgs.Graphics().BitBlt(repaintRect.iTl, iBackBuffer->Bitmap, repaintRect);
        }
    else
        {
        PaintEventArgs repaintArgs(aArgs.Graphics(), repaintRect);
        OnPaint(repaintArgs);
        PaintEventArgs dispatchArgs(aArgs.Graphics(), clientRect);
        DispatchPaint(dispatchArgs);
        }
    }

// ----------------------------------------------------------------------------
// Control::DispatchPaint
// Dispatches paint event to children.
// ----------------------------------------------------------------------------
//
void Control::DispatchPaint(PaintEventArgs& aArgs)
    {
    TRect clipRect(aArgs.ClipRectangle());
    // Dispatch the paint event to children
    for (TInt i = 0; i < iControls.Count(); ++i)
        {
        if (iControls[i]->Bounds().Intersects(clipRect))
            {
            iControls[i]->RaisePaintEvent(iControls[i], aArgs);
            }
        }
    }

// ----------------------------------------------------------------------------
// Control::RaiseKeyEvent
// Raises the key events in the correct order.
// ----------------------------------------------------------------------------
//
void Control::RaiseKeyEvent(Control* aSender, KeyEventArgs& aArgs)
    {
    if (NULL != FocusedChild)
        {
        FocusedChild->RaiseKeyEvent(aSender, aArgs);
        }

    if (!aArgs.Handled())
        {
        switch (aArgs.EventType)
            {
            case EEventKeyDown:
                {
                OnKeyDown(aArgs);
                break;
                }
            case EEventKey:
                {
                KeyPressEventArgs args(aArgs);
                OnKeyPress(args);
                break;
                }
            case EEventKeyUp:
                {
                OnKeyUp(aArgs);
                break;
                }
            default:
                break;
            }
        }
    }

// ----------------------------------------------------------------------------
// Control::RaiseMouseEvent
// Raises the mouse events, in the correct order.
// ----------------------------------------------------------------------------
//
void Control::RaiseMouseEvent(Control* aSender, MouseEventArgs& aArgs)
    {
    TRACE_FUNC_ENTRY;
    TRACE_INFO((_L("Control name: %S"), &Name()));
    TPoint clientPosition = PointToClient(aArgs.Location());
    Control* child = GetFocusingChildAtPointRecursive(clientPosition);
    if (NULL != child && child->CanFocus)
        {
        TRACE_INFO((_L("Control::RaiseMouseEvent got child: %S"), &child->Name()));
        child->RaiseMouseEvent(aSender, aArgs);
        }
    else
        {
        TRACE_INFO((_L("Control::RaiseMouseEvent check event type")));
        switch (aArgs.Type())
            {
            case TPointerEvent::EButton1Up:
            case TPointerEvent::EButton2Up:
            case TPointerEvent::EButton3Up:
                {
                TRACE_INFO((_L("Control::RaiseMouseEvent button up")));
                MouseEventArgs args(aArgs, clientPosition);
                OnMouseUp(aArgs);
                if (TRect(Size).Contains(clientPosition))
                    {
                    OnDragLeave();
                    if (this == aArgs.OriginatingControl())
                        {
                        OnMouseClick(aArgs);
                        OnClick();
                        }
                    }
                aArgs.SetOriginatingControl(NULL);
                aArgs.SetOriginatingLocation(TPoint(0, 0));
                aArgs.SetDragSource(NULL);
                aArgs.SetDragOver(NULL);
                break;
                }
            case TPointerEvent::EButton1Down:
            case TPointerEvent::EButton2Down:
            case TPointerEvent::EButton3Down:
                {
                TRACE_INFO((_L("Control::RaiseMouseEvent button down")));
                aArgs.SetOriginatingControl(this);
                aArgs.SetOriginatingLocation(aArgs.Location());
                aArgs.SetDragSource(this);
                aArgs.SetDragOver(this);
                MouseEventArgs args(aArgs, clientPosition);
                OnMouseDown(args);
                DragEventArgs dragArgs(DragDropEffect::All, NULL, 0, clientPosition, aArgs.DragSource());
                OnDragEnter(dragArgs);
                break;
                }
            case TPointerEvent::EDrag:
                {
                TRACE_INFO((_L("Control::RaiseMouseEvent drag")));
                DragEventArgs args(DragDropEffect::All, NULL, 0, clientPosition, aArgs.DragSource());
                TRect innerRect(Size);
                if (aArgs.DragOver() == this && innerRect.Contains(clientPosition))
                    {
                    OnDragOver(args);
                    }
                else if (aArgs.DragOver() == this)
                    {
                    OnDragLeave();
                    aArgs.SetDragOver(NULL);
                    }
                else if (innerRect.Contains(clientPosition))
                    {
                    if (aArgs.DragOver() != NULL)
                        {
                        aArgs.DragOver()->OnDragLeave();
                        }
                    aArgs.SetDragOver(this);
                    OnDragEnter(args);
                    OnDragOver(args);
                    }
                break;
                }
            default:
                {
                break;
                }
            }
        }
    TRACE_FUNC_EXIT;
    }

// ----------------------------------------------------------------------------
// Control::AsyncHandleCommandL
// Handles asynchronous commands.
// ----------------------------------------------------------------------------
//
void Control::AsyncHandleCommandL(const TInt& aCommand)
    {
    if (aCommand == ECommandLayout)
        {
        Layout();
        }
    }

// ----------------------------------------------------------------------------
// Control::OnClick
// Called before raising the Click event.
// ----------------------------------------------------------------------------
//
void Control::OnClick()
    {
    TriggerEvent(Click, this);
    }

// ----------------------------------------------------------------------------
// Control::OnDoubleClick
// Called before raising the DoubleClick event.
// ----------------------------------------------------------------------------
//
void Control::OnDoubleClick()
    {
    TriggerEvent(DoubleClick, this);
    }

// ----------------------------------------------------------------------------
// Control::OnControlAdded
// Called before raising the ControlAdded event.
// ----------------------------------------------------------------------------
//
void Control::OnControlAdded(Control* aControl)
    {
    TriggerEvent(ControlAdded, this, aControl);
    }

// ----------------------------------------------------------------------------
// Control::OnControlRemoved
// Called before raising the ControlRemoved event.
// ----------------------------------------------------------------------------
//
void Control::OnControlRemoved(Control* aControl)
    {
    TriggerEvent(ControlRemoved, this, aControl);
    }

// ----------------------------------------------------------------------------
// Control::OnDragDrop
// Called before raising the DragDrop event.
// ----------------------------------------------------------------------------
//
void Control::OnDragDrop(DragEventArgs& aArgs)
    {
    TriggerEvent(DragDrop, this, aArgs);
    }

// ----------------------------------------------------------------------------
// Control::OnDragEnter
// Called before raising the DragEnter event.
// ----------------------------------------------------------------------------
//
void Control::OnDragEnter(DragEventArgs& aArgs)
    {
    TriggerEvent(DragEnter, this, aArgs);
    }

// ----------------------------------------------------------------------------
// Control::OnDragLeave
// Called before raising the DragLeave event.
// ----------------------------------------------------------------------------
//
void Control::OnDragLeave()
    {
    TriggerEvent(DragLeave, this);
    }

// ----------------------------------------------------------------------------
// Control::OnDragOver
// Called before raising the DragOver event.
// ----------------------------------------------------------------------------
//
void Control::OnDragOver(DragEventArgs& aArgs)
    {
    TriggerEvent(DragOver, this, aArgs);
    }

// ----------------------------------------------------------------------------
// Control::OnGotFocus
// Called before raising the GotFocus event.
// ----------------------------------------------------------------------------
//
void Control::OnGotFocus()
    {
    TriggerEvent(GotFocus, this);
    }

// ----------------------------------------------------------------------------
// Control::OnKeyDown
// Called before raising the KeyDown event.
// ----------------------------------------------------------------------------
//
void Control::OnKeyDown(KeyEventArgs& aArgs)
    {
    TriggerEvent(KeyDown, this, aArgs);
    }

// ----------------------------------------------------------------------------
// Control::OnKeyPress
// Called before raising the KeyPress event.
// ----------------------------------------------------------------------------
//
void Control::OnKeyPress(KeyPressEventArgs& aArgs)
    {
    TriggerEvent(KeyPress, this, aArgs);
    }

// ----------------------------------------------------------------------------
// Control::OnKeyUp
// Called before raising the KeyUp event.
// ----------------------------------------------------------------------------
//
void Control::OnKeyUp(KeyEventArgs& aArgs)
    {
    TriggerEvent(KeyUp, this, aArgs);
    }

// ----------------------------------------------------------------------------
// Control::OnLostFocus
// Called before raising the LostFocus event.
// ----------------------------------------------------------------------------
//
void Control::OnLostFocus()
    {
    TriggerEvent(LostFocus, this);
    }

// ----------------------------------------------------------------------------
// Control::OnMouseClick
// Called before raising the MouseClick event.
// ----------------------------------------------------------------------------
//
void Control::OnMouseClick(MouseEventArgs& aArgs)
    {
    TriggerEvent(MouseClick, this, aArgs);
    }

// ----------------------------------------------------------------------------
// Control::OnMouseDoubleClick
// Called before raising the MouseDoubleClick event.
// ----------------------------------------------------------------------------
//
void Control::OnMouseDoubleClick(MouseEventArgs& aArgs)
    {
    TriggerEvent(MouseDoubleClick, this, aArgs);
    }

// ----------------------------------------------------------------------------
// Control::OnMouseDown
// Called before raising the MouseDown event.
// ----------------------------------------------------------------------------
//
void Control::OnMouseDown(MouseEventArgs& aArgs)
    {
    if (CanFocus && !Focused)
        {
        OnRequestFocus();
        }
    TriggerEvent(MouseDown, this, aArgs);
    }

// ----------------------------------------------------------------------------
// Control::OnMouseUp
// Called before raising the MouseUp event.
// ----------------------------------------------------------------------------
//
void Control::OnMouseUp(MouseEventArgs& aArgs)
    {
    TriggerEvent(MouseUp, this, aArgs);
    }

// ----------------------------------------------------------------------------
// Control::OnPaint
// Called before raising the Paint event.
// ----------------------------------------------------------------------------
//
void Control::OnPaint(PaintEventArgs& aArgs)
    {
    if (Enabled)
        {
        Paint(this, aArgs);
        OnValidated();
        }
    }

// ----------------------------------------------------------------------------
// Control::OnInvalidated
// Called before raising the Invalidated event.
// ----------------------------------------------------------------------------
//
void Control::OnInvalidated()
    {
    if (Enabled)
        {
        IsInvalidated = ETrue;
        InvalidateWindow(RectangleToScreen(InvalidatedRect));
        Invalidated(this);
        }
    }

void Control::OnValidated()
    {
    if (Enabled)
        {
        IsInvalidated = EFalse;
        InvalidatedRect = TRect();
        Validated(this);
        }
    }

// ----------------------------------------------------------------------------
// Control::OnRequestFocus
// Triggers the RequestFocus event.
// ----------------------------------------------------------------------------
//
void Control::OnRequestFocus()
    {
    TriggerEvent(RequestFocus, this);
    }

// ----------------------------------------------------------------------------
// Control::DoubleBuffered_ValueChanged
// Handles DoubleBuffered property change.
// ----------------------------------------------------------------------------
//
void Control::DoubleBuffered_ValueChanged(const PropertyBase<TBool>& aDoubleBuffered)
    {
    if (aDoubleBuffered)
        {
        Size.ValueChanged += MethodHandler(this, &Control::DoubleBuffered_Size_ValueChanged);
        iBackBuffer = new (ELeave) BackBuffer();
        iBackBuffer->Create(Size);
        }
    else
        {
        Size.ValueChanged -= MethodHandler(this, &Control::DoubleBuffered_Size_ValueChanged);
        delete iBackBuffer;
        iBackBuffer = NULL;
        }
    }

// ----------------------------------------------------------------------------
// Control::DoubleBuffered_Size_ValueChanged
// Handles DoubleBuffered_Size property change.
// ----------------------------------------------------------------------------
//
void Control::DoubleBuffered_Size_ValueChanged(const PropertyBase<TSize>& aSize)
    {
    iBackBuffer->Resize(aSize);
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Control::Focus_ValueChanged
// Handles Focus property change.
// ----------------------------------------------------------------------------
//
void Control::Focused_ValueChanged(const PropertyBase<TBool>& aFocused)
    {
    if (aFocused())
        OnGotFocus();
    else
        OnLostFocus();
    }

// ----------------------------------------------------------------------------
// Control::Margin_Changed
// Handles Margin property change.
// ----------------------------------------------------------------------------
//
void Control::Margin_Changed(const PropertyBase<TRect>& /*aMargin*/)
    {
    CalculateClientRect();
    }

// ----------------------------------------------------------------------------
// Control::Size_Changed
// Handles Size property change.
// ----------------------------------------------------------------------------
//
void Control::Size_Changed(const PropertyBase<TSize>& aSize)
    {
    CalculateClientRect();
    Arrange(aSize);
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Control::Child_RequestFocus
// Called when a child requests focus
// ----------------------------------------------------------------------------
//
void Control::Child_RequestFocus(Control* aChild)
    {
    FocusChild(aChild);
    }

// ----------------------------------------------------------------------------
// Control::Visible_Changed
// Handles Visible property change.
// ----------------------------------------------------------------------------
//
void Control::Visible_Changed(const PropertyBase<TBool>& /*aVisible*/)
    {
    Redraw();
    }

// ----------------------------------------------------------------------------
// Control::InvalidateWindow
// Invalidates a window. The effect is a redraw request.
// ----------------------------------------------------------------------------
//
void Control::InvalidateWindow(const TRect& aRect)
    {
    if (Window)
        {
        Window->Invalidate(aRect);
        }
    }

// ----------------------------------------------------------------------------
// Control::FocusChild
// Focuses a child.
// ----------------------------------------------------------------------------
//
TBool Control::FocusChild(Control* aChild)
    {
    Focus();
    ASSERT(Focused());

    if (aChild->Focused)
        {
        ASSERT(aChild == FocusedChild);
        return ETrue;
        }
    else
        {
        if (NULL != FocusedChild())
            {
            // TODO: perform some validation if the control can lose focus?
            FocusedChild()->Focused = EFalse;
            }
        FocusedChild = aChild;
        FocusedChild()->Focused = ETrue;
        return ETrue;
        }
    }

// ----------------------------------------------------------------------------
// Control::Measure
// Measures the size in layout required for child elements
// ----------------------------------------------------------------------------
//
TSize Control::Measure(const TSize& /*aAvailableSize*/)
    {
    return PreferredSize;
    }

// ----------------------------------------------------------------------------
// Contorl::Arrange
// Positions child elements
// ----------------------------------------------------------------------------
//
TSize Control::Arrange(const TSize& aFinalSize)
    {
    return aFinalSize;
    }

// ----------------------------------------------------------------------------
// Control::LayoutDeferred
// Triggers layout if it was not already triggered.
// ----------------------------------------------------------------------------
//
void Control::LayoutDeferred()
    {
    const Control* topLevelControl = TopLevelControl();
    if (!topLevelControl->CommandPosted(ECommandLayout))
        {
        topLevelControl->PostCommandL(ECommandLayout);
        }
    }

// ----------------------------------------------------------------------------
// Control::Layout
// Performs layout. Base implementation does nothing
// ----------------------------------------------------------------------------
//
void Control::Layout()
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Control::InitFromXml
// Initializes a control from XML specification.
// ----------------------------------------------------------------------------
//
void Control::InitFromXml()
    {
    // No implementation required.
    }

// ----------------------------------------------------------------------------
// Control::MarginsSize
// Calculates the margins size.
// ----------------------------------------------------------------------------
//
TSize Control::MarginsSize() const
    {
    TRect margin = Margin;
    return TSize(margin.iTl.iX + margin.iBr.iX, margin.iTl.iY + margin.iBr.iY);
    }

// ----------------------------------------------------------------------------
// Control::GetWindow
// Retrieves the window attached to this control.
// ----------------------------------------------------------------------------
//
RWindow* Control::GetWindow() const
    {
    if ((iWindow == NULL) && (Parent() != NULL))
        {
        iWindow = Parent()->GetWindow();
        }
    return iWindow;
    }

// ----------------------------------------------------------------------------
// Control::GetScreen
// Retrieves the screen device object.
// ----------------------------------------------------------------------------
//
CWsScreenDevice& Control::GetScreen() const
    {
    if (NULL == iScreen)
        {
        ASSERT(NULL != Parent());
        iScreen = &Parent()->GetScreen();
        }
    return *iScreen;
    }

// ----------------------------------------------------------------------------
// Control::GetApplication
// Retreives the application object.
// ----------------------------------------------------------------------------
//
Application& Control::GetApplication() const
    {
    if (NULL != iApplication)
        {
        ASSERT(NULL != Parent());
        iApplication = &Parent()->GetApplication();
        }
    return *iApplication;
    }

// ----------------------------------------------------------------------------
// Control::GetControlsArray
// Retrieves the controls array.
// ----------------------------------------------------------------------------
//
const RControlsArray& Control::GetControlsArray() const
    {
    return iControls;
    }

// ----------------------------------------------------------------------------
// Control::CalculateClientRect
// Calculates the client rectangle and the display rectangle.
// ----------------------------------------------------------------------------
//
void Control::CalculateClientRect()
    {
    TRect clientRect(Size);
    clientRect.iTl += Margin().iTl;
    clientRect.iBr -= Margin().iBr;
    clientRect.iBr.iX = Max(clientRect.iBr.iX, clientRect.iTl.iX);
    clientRect.iBr.iY = Max(clientRect.iBr.iY, clientRect.iTl.iY);
    DisplayRectangle = clientRect;
    ClientRectangle = clientRect;
    }

// ----------------------------------------------------------------------------
// Control::InvalidateWithParent
// Invalidates this control and invalidates the parent.
// ----------------------------------------------------------------------------
//
void Control::InvalidateControl(const TRect& aRect)
    {
    TRect invalidateRect = aRect;
    TRect clientRect(Size);
    invalidateRect.Intersection(clientRect);
    if (!invalidateRect.IsEmpty())
        {
        TRect rect(InvalidatedRect);
        if (rect.IsEmpty())
            {
            rect = invalidateRect;
            }
        else
            {
            rect.BoundingRect(invalidateRect);
            }
        InvalidatedRect = rect;
        OnInvalidated();
        }
    }

// ----------------------------------------------------------------------------
// Control::InvalidateParents
// Invalidates the parents based on InvalidatedRect.
// ----------------------------------------------------------------------------
//
void Control::InvalidateParents()
    {
    TRect invalidatedRect = InvalidatedRect;
    Control* ancestor = Parent;
    TPoint location = Location;
    while (ancestor)
        {
        invalidatedRect.Move(location);
        ancestor->IsInvalidated = ETrue;
        TRect ancestorInvRect = ancestor->InvalidatedRect;
        if (ancestorInvRect.IsEmpty())
            {
            ancestorInvRect = invalidatedRect;
            }
        else
            {
            ancestorInvRect.BoundingRect(invalidatedRect);
            }
        ancestor->InvalidatedRect = ancestorInvRect;
        location = ancestor->Location;
        ancestor = ancestor->Parent;
        }
    }
