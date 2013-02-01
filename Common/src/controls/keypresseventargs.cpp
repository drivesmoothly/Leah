#include "keypresseventargs.h"
#include "keyeventargs.h"
#include "propertybind.h"

// ----------------------------------------------------------------------------
// KeyPressEventArgs::KeyPressEventArgs
// Constructor.
// ----------------------------------------------------------------------------
//
KeyPressEventArgs::KeyPressEventArgs(TUint16 aChar)
: KeyChar(aChar)
    {
    // No implementation required.
    }

// ----------------------------------------------------------------------------
// KeyPressEventArgs::KeyPressEventArgs
// Constructor.
// ----------------------------------------------------------------------------
//
KeyPressEventArgs::KeyPressEventArgs(KeyEventArgs& aArgs)
: KeyChar(aArgs.KeyCode)
, _args(&aArgs)
    {
    BindTwoWay(Handled, aArgs.Handled);
    }
