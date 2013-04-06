#ifndef METHODCOMPARER_H_INCLUDED
#define METHODCOMPARER_H_INCLUDED

#include "handlercomparer.h"

/// Forwards
class MethodHandlerBase;

///
/// Compares method handlers
///
class MethodHandlerComparer : public HandlerComparer
{
public: // Constructors and destructor
    /// Constructor
    MethodHandlerComparer(MethodHandlerBase& handler);

public: // From HandlerVisitor
    /// Visit handlers not specially treated here.
    void Visit(HandlerBase& handler);

    /// Visit member function handlers.
    void Visit(MethodHandlerBase& handler);

    /// Visit non-member or static member function handlers.
    void Visit(FunctionHandlerBase& handler);

private: // Data
    /// The base handler
    MethodHandlerBase& _baseHandler;
};

#endif // METHODCOMPARER_H_INCLUDED
