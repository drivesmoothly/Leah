#ifndef KEYPRESSEVENTARGS_H_
#define KEYPRESSEVENTARGS_H_

// USER INCLUDES
#include "property.h"

// FORWARDS
class KeyEventArgs;

/**
 * Stores the event args for the KeyPress event.
 */
class KeyPressEventArgs
    {
public: // Properties
    PropertyRead<TUint16> KeyChar;
    Property<TBool> Handled;

public: // Constructors and destructor
    KeyPressEventArgs(TUint16 aChar);
    KeyPressEventArgs(KeyEventArgs& aArgs);

private: // Data
    KeyEventArgs* _args;
    };

#endif //KEYPRESSEVENTARGS_H_
