#include "mouseeventargs.h"

// ----------------------------------------------------------------------------
// MouseEventArgs::MouseEventArgs
// Construtor.
// ----------------------------------------------------------------------------
//
MouseEventArgs::MouseEventArgs(TPointerEvent::TType aType, const TPoint& aLocation)
: _location(aLocation)
, _type(aType)
, _handled(EFalse)
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::MouseEventArgs
// Construtor.
// ----------------------------------------------------------------------------
//
MouseEventArgs::MouseEventArgs(const MouseEventArgs& aArgs, const TPoint& aLocation)
: _location(aLocation)
, _type(aArgs.Type())
, _originatingControl(aArgs.OriginatingControl())
, _dragSource(aArgs.DragSource())
, _handled(aArgs.Handled())
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// MouseEventArgs::~MouseEventArgs
// Destructor.
// ----------------------------------------------------------------------------
//
MouseEventArgs::~MouseEventArgs()
    {
    // No implementation required
    }
