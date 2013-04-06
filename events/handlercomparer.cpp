#include "handlercomparer.h"
#include "handlerbase"

/// Default constructor
HandlerComparer::HandlerComparer()
{
    // No implementation required.
}

/// Compare function
bool HandlerComparer::Equals(HandlerBase& handler)
{
    handler.Accept(*this);
    return _equalsResult;
}

/// Find a handler in a linked list of handlers
HandlerBase* HandlerComparer::Find(HandlerBase& handler)
{
    return NULL;
}
