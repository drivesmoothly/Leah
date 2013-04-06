#ifndef FUNCTIONHANDLERCOMPARER_H
#define FUNCTIONHANDLERCOMPARER_H

#include "handlercomparer.h"

/// Forwards
class FunctionHandlerBase;
class MethodHandlerBase;

///
/// Compares function handlers
///
class FunctionHandlerComparer : public HandlerComparer
{
public: // Constructors and destructor
    /// Constructor
    FunctionHandlerComparer(FunctionHandlerBase& handler);

public: // From HandlerVisitor
    /// Visit handlers not specially treated here.
    void Visit(HandlerBase& handler);

    /// Visit member function handlers.
    void Visit(MethodHandlerBase& handler);

    /// Visit non-member or static member function handlers.
    void Visit(FunctionHandlerBase& handler);

private: // Data
    /// The base handler
    FunctionHandlerBase& _baseHandler;
};

#endif // FUNCTIONHANDLERCOMPARER_H
