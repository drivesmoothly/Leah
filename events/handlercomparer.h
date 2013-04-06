#ifndef HANDLERCOMPARER_H_INCLUDED
#define HANDLERCOMPARER_H_INCLUDED

#include "handlervisitor"

/// Forwards
class HandlerBase;

///
/// Base class for comparer classes
///
class HandlerComparer : public HandlerVisitor
{
protected: // Constructors and destructor
    /// Default constructor
    HandlerComparer();

public: // New functions
    /// Compares the selected handler with the given one.
    bool Equals(HandlerBase& handler);

    /// Finds a handler in a linked list of handlers.
    HandlerBase* Find(HandlerBase& handler);

protected: // Data
    /// Stores the comparison result
    bool _equalsResult;
};

#endif // HANDLERCOMPARER_H_INCLUDED
