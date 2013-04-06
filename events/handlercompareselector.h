#ifndef HANDLERCOMPARESELECTOR_INCLUDED
#define HANDLERCOMPARESELECTOR_INCLUDED

#include "handlervisitor"
#include <memory>

/// Forwards
class HandlerComparer;
class MethodHandlerBase;
class FunctionHandlerBase;

///
/// Selects which handler comparer to use
///
class HandlerComparerSelector : public HandlerVisitor
{
public: // New functions
    /// Create the right comparer
    std::shared_ptr<HandlerComparer> CreateComparer(HandlerBase& handler);

public: // From HandlerVisitor
    /// Throw an exception for any other type of handler.
    void Visit(HandlerBase&);

    /// Create a comparer for method handlers.
    void Visit(MethodHandlerBase& handler);

    /// Create a comparer for function handlers.
    void Visit(FunctionHandlerBase& handler);

private: // Data
    std::shared_ptr<HandlerComparer> _comparer;
};

#endif //HANDLERCOMPARESELECTOR_INCLUDED
