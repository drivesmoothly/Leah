/*
 -------------------------------------------------------------------------------
 Name        : eventsbase.h
 Author      : Marius Crisan
 Description : Defines events and handlers.
 -------------------------------------------------------------------------------
 */
#ifndef __EVENTSBASE_H
#define __EVENTSBASE_H

// SYSTEM INCLUDES
#include <e32std.h>
#include "handlersbase.h"

// Class for specifying no argument was passed
class EventNoArg {};

/**
 * MEventBase template partial specialization interface declaration.
 * Takes 3 template arguments.
 *
 * This is an abstract class intended for inheritance.
 */
template <class T1 = EventNoArg, class T2 = EventNoArg, class T3 = EventNoArg>
class MEventBase
{
public:
    /**
     * Destructor.
     */
    virtual ~MEventBase() {};
    /**
     * Operator to add a handler to the event.
     * @param aHandler The new handler.
     * @return A reference to this object.
     */
    virtual MEventBase<T1, T2, T3>& operator +=(const MHandlerBase<T1, T2, T3>& aHandler) = 0;
    /**
     * Operator to remove a handler from the event.
     * @param aHandler The handler to remove.
     * @return A reference to the this object.
     */
    virtual MEventBase<T1, T2, T3>& operator -=(const MHandlerBase<T1, T2, T3>& aHandler) = 0;

    /**
     * Operator to call the handler(s) of this event (raise the event).
     */
    virtual void operator()(T1 aArg1, T2 aArg2, T3 aArg3) = 0;
    /**
     * Operator that retrieves the number of handlers registered to the event.
     */
    virtual operator TInt() = 0;
};

/**
 * MEventBase template partial specialization interface declaration.
 * Takes no template arguments.
 *
 * This is an abstract class intended for inheritance.
 */
template <>
class MEventBase<EventNoArg, EventNoArg, EventNoArg>
{
public:
    /**
     * Destructor.
     */
    virtual ~MEventBase() {};
    /**
     * Operator to add a handler to the event.
     */
    virtual MEventBase& operator +=(const MHandlerBase<>& aHandler) = 0;
    /**
     * Operator to remove a handler from the event.
     */
    virtual MEventBase& operator -=(const MHandlerBase<>& aHandler) = 0;
    /**
     * Operator to call the handler(s) of this event (raise the event).
     */
    virtual void operator()() = 0;
    /**
     * Operator that retrieves the number of handlers registered to the event.
     */
    virtual operator TInt() = 0;
};

/**
 * MEventBase template partial specialization interface declaration.
 * Takes 1 template argument.
 *
 * This is an abstract class intended for inheritance.
 */
template <class T>
class MEventBase<T, EventNoArg, EventNoArg>
{
public:
    /**
     * Destructor.
     */
    virtual ~MEventBase() {};
    /**
     * Operator to add a handler to the event.
     */
    virtual MEventBase<T>& operator +=(const MHandlerBase<T>& aHandler) = 0;
    /**
     * Operator to remove a handler from the event.
     */
    virtual MEventBase<T>& operator -=(const MHandlerBase<T>& aHandler) = 0;
    /**
     * Operator to call the handler(s) of this event (raise the event).
     */
    virtual void operator()(T aArg) = 0;
    /**
     * Operator that retrieves the number of handlers registered to the event.
     */
    virtual operator TInt() = 0;
};

/**
 * MEventBase template partial specialization interface declaration.
 * Takes 2 template arguments.
 *
 * This is an abstract class intended for inheritance.
 */
template <class T1, class T2>
class MEventBase<T1, T2, EventNoArg>
{
public:
    /**
     * Destructor.
     */
    virtual ~MEventBase() {};
    /**
     * Operator to add a handler to the event.
     */
    virtual MEventBase<T1, T2>& operator +=(const MHandlerBase<T1, T2>& aHandler) = 0;
    /**
     * Operator to remove a handler from the event.
     */
    virtual MEventBase<T1, T2>& operator -=(const MHandlerBase<T1, T2>& aHandler) = 0;
    /**
     * Operator to call the handler(s) of this event (raise the event).
     */
    virtual void operator()(T1 aArg1, T2 aArg2) = 0;
    /**
     * Operator that retrieves the number of handlers registered to the event.
     */
    virtual operator TInt() = 0;
};

#endif //__EVENTSBASE_H
