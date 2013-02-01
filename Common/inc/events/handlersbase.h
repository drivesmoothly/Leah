#ifndef HANDLERSBASE_H_
#define HANDLERSBASE_H_

// SYSTEM INCLUDES
#include <e32std.h>

class MHandlerVisitor;
class HandlerNoArg {};

/**
 * Base class for all handlers.
 */
class _MHandlerBase
    {
public:
    virtual ~_MHandlerBase() {}

    virtual void Accept(MHandlerVisitor& aVisitor) const = 0;
    virtual TBool Equals(const _MHandlerBase& aInstance) = 0;
    };


/**
 * MHandlerBase template interface declaration.
 * Interface for handlers with 3 arguments.
 */
template <class T1 = HandlerNoArg, class T2 = HandlerNoArg, class T3 = HandlerNoArg>
class MHandlerBase : public _MHandlerBase
{
public:
    /**
     * Calls the handler.
     */
    virtual void Call(T1 aArg1, T2 aArg2, T3 aArg3) = 0;
    /**
     * Clones the handler.
     */
    virtual MHandlerBase<T1, T2, T3>* CloneL() const = 0;
};

/**
 * MHandlerBase template partial specialization interface declaration.
 * Interface for handlers with no arguments.
 */
template <>
class MHandlerBase<HandlerNoArg, HandlerNoArg, HandlerNoArg> : public _MHandlerBase
{
public:
    /**
     * Calls the handler.
     */
    virtual void Call() = 0;
    /**
     * Clones the handler.
     */
    virtual MHandlerBase<>* CloneL() const = 0;
};

/**
 * MHandlerBase template partial specialization interface declaration.
 * Interface for handlers with 1 argument.
 */
template <class T>
class MHandlerBase<T, HandlerNoArg, HandlerNoArg> : public _MHandlerBase
{
public:
    /**
     * Calls the handler.
     */
    virtual void Call(T aArg) = 0;
    /**
     * Clones the handler.
     */
    virtual MHandlerBase<T>* CloneL() const = 0;
};

/**
 * MHandlerBase template partial specialization interface declaration.
 * Interface for handlers with 2 arguments.
 */
template <class T1, class T2>
class MHandlerBase<T1, T2, HandlerNoArg> : public _MHandlerBase
{
public:
    /**
     * Calls the handler.
     */
    virtual void Call(T1 aArg1, T2 aArg2) = 0;
    /**
     * Clones the handler.
     */
    virtual MHandlerBase<T1, T2>* CloneL() const = 0;
};

#endif //HANDLERSBASE_H_
