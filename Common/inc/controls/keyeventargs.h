#ifndef KEYEVENTARGS_H_
#define KEYEVENTARGS_H_

#include "property.h"

class KeyEventArgs
    {
public: // Properties
    PropertyReadExt<TBool, KeyEventArgs> Alt;
    PropertyReadExt<TBool, KeyEventArgs> Control;
    PropertyReadExt<TBool, KeyEventArgs> Shift;
    Property<TBool> Handled;
    PropertyRead<TInt> KeyCode;
    PropertyRead<TInt> Modifiers;
    Property<TBool> SuppressKeyPress;
    PropertyRead<TInt> ScanCode;
    PropertyRead<TInt> EventType;

public: // Constructors and destructor
    KeyEventArgs(TInt aCode, TInt aScanCode, TInt aModifiers, TInt aEventType);

protected: // New functions
    TBool GetAlt() const;
    TBool GetControl() const;
    TBool GetShift() const;
    };

#endif //KEYEVENTARGS_H_
