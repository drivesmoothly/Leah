#include "handlercompareselector.h"
#include "handlercomparer.h"
#include "notimpl.h"
#include "handlerbase"
#include "methodcomparer.h"
#include "functionhandlercomparer.h"

/// Creates the right comparer for the given Handler
std::shared_ptr<HandlerComparer> HandlerComparerSelector::CreateComparer(HandlerBase& handler)
{
    handler.Accept(*this);
    return _comparer;
}

/// Create a comparer for other types of handlers
void HandlerComparerSelector::Visit(HandlerBase&)
{
    _comparer.reset();
}

/// Creates a comparer for Method Handlers
void HandlerComparerSelector::Visit(MethodHandlerBase& handler)
{
    _comparer.reset(new MethodHandlerComparer(handler));
}

/// Creates a comparer for Function Handlers
void HandlerComparerSelector::Visit(FunctionHandlerBase& handler)
{
    _comparer.reset(new FunctionHandlerComparer(handler));
}
