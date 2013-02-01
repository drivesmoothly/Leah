
// ----------------------------------------------------------------------------
// MouseEventArgs::Button
// Retrieves the button for the event.
// ----------------------------------------------------------------------------
//
TInt MouseEventArgs::Button() const
    {
    switch (Type())
        {
        case TPointerEvent::EButton1Down:
        case TPointerEvent::EButton1Up:
            {
            return MouseButton::Left;
            }
        case TPointerEvent::EButton2Down:
        case TPointerEvent::EButton2Up:
            {
            return MouseButton::Right;
            }
        case TPointerEvent::EButton3Down:
        case TPointerEvent::EButton3Up:
            {
            return MouseButton::Middle;
            }
        default:
            return MouseButton::None;
        }
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::Location
// Retrieves the location for the event.
// ----------------------------------------------------------------------------
//
const TPoint& MouseEventArgs::Location() const
    {
    return _location;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::X
// Retrieves the X coordinate for the event.
// ----------------------------------------------------------------------------
//
TInt MouseEventArgs::X() const
    {
    return _location.iX;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::Y
// Retrieves the Y coordinate for this event.
// ----------------------------------------------------------------------------
//
TInt MouseEventArgs::Y() const
    {
    return _location.iY;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::Type
// Retrieves the type of event.
// ----------------------------------------------------------------------------
//
TPointerEvent::TType MouseEventArgs::Type() const
    {
    return _type;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::OriginatingControl
// Retrieves the originating control for this event.
// ----------------------------------------------------------------------------
//
Control* MouseEventArgs::OriginatingControl() const
    {
    return _originatingControl;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::SetOriginatingControl
// Sets the originating control for this event.
// ----------------------------------------------------------------------------
//
void MouseEventArgs::SetOriginatingControl(Control* aControl)
    {
    _originatingControl = aControl;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::OriginatingLocation
// Retrieves the originating location for this event.
// ----------------------------------------------------------------------------
//
const TPoint& MouseEventArgs::OriginatingLocation() const
    {
    return _originatingLocation;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::SetOriginatingLocation
// Sets the originating location for this event.
// ----------------------------------------------------------------------------
//
void MouseEventArgs::SetOriginatingLocation(const TPoint& aLocation)
    {
    _originatingLocation = aLocation;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::DragSource
// Retrieves the drag source for this event.
// ----------------------------------------------------------------------------
//
Control* MouseEventArgs::DragSource() const
    {
    return _dragSource;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::SetDragSource
// Sets the drag source for this event.
// ----------------------------------------------------------------------------
//
void MouseEventArgs::SetDragSource(Control* aDragSource)
    {
    _dragSource = aDragSource;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::DragOver
// Retrieves the latest control that was dragged over.
// ----------------------------------------------------------------------------
//
Control* MouseEventArgs::DragOver() const
    {
    return _dragOver;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::SetDragOver
// Sets the latest control that was dragged over for this event.
// ----------------------------------------------------------------------------
//
void MouseEventArgs::SetDragOver(Control* aDragOver)
    {
    _dragOver = aDragOver;
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::Handled
// Retrieves if the event was handled.
// ----------------------------------------------------------------------------
//
TBool MouseEventArgs::Handled() const
    {
    return _handled;
    }
