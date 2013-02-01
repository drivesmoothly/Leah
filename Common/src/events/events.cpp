#include "events.h"

/**
 * Event::operator ()
 * Call operator for no arguments.
 */
EXPORT_C void Event<EventNoArg, EventNoArg, EventNoArg>::operator ()()
    {
    for (TInt i = 0; i < Base::iHandlersArray.Count(); ++i)
        {
        Base::iHandlersArray[i]->Call();
        }
    }
