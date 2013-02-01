#include "drageventargs.h"

DragEventArgs::DragEventArgs(TInt aAllowedEffect, DataObject* aData, TInt aKeyState, const TPoint& aLocation, Control* aDragSource)
: AllowedEffect(aAllowedEffect)
, Data(aData)
, KeyState(aKeyState)
, X(*this, &DragEventArgs::GetX)
, Y(*this, &DragEventArgs::GetY)
, Location(aLocation)
, DragSource(aDragSource)
    {
    // No implementation required
    }

DragEventArgs::~DragEventArgs()
    {
    // No implementation required
    }

TInt DragEventArgs::GetX() const
    {
    return Location.iX;
    }

TInt DragEventArgs::GetY() const
    {
    return Location.iY;
    }
