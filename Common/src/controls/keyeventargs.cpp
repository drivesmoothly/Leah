#include "keyeventargs.h"
#include <e32keys.h>

KeyEventArgs::KeyEventArgs(TInt aCode, TInt aScanCode, TInt aModifiers, TInt aEventType)
: Alt(*this, &KeyEventArgs::GetAlt)
, Control(*this, &KeyEventArgs::GetControl)
, Shift(*this, &KeyEventArgs::GetShift)
, KeyCode(aCode)
, Modifiers(aModifiers)
, ScanCode(aScanCode)
, EventType(aEventType)
    {
    // No implementation required
    }

TBool KeyEventArgs::GetAlt() const
    {
    return Modifiers & EModifierAlt;
    }

TBool KeyEventArgs::GetControl() const
    {
    return Modifiers & EModifierCtrl;
    }

TBool KeyEventArgs::GetShift() const
    {
    return Modifiers & EModifierShift;
    }
