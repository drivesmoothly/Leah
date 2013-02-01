/*
 -------------------------------------------------------------------------------
 Name        : events.h
 Author      : Marius Crisan
 Description : Concrete events.
 -------------------------------------------------------------------------------
 */
#ifndef __EVENTS_H
#define __EVENTS_H

// SYSTEM INCLUDES
#include <e32base.h>

// USER INCLUDES
#include "eventsbase.h"

// CLASSES

/**
 * Base class for events.
 * Groups together common operations like appending, removing handlers and returning the
 * number of registered handlers.
 */
template<class EventBase, class HandlerBase>
class _REvent : EventBase
	{
public:
	virtual ~_REvent();
	EventBase& operator +=(const HandlerBase& aHandler);
	EventBase& operator -=(const HandlerBase& aHandler);
	operator TInt();
protected:
	RPointerArray<HandlerBase> iHandlersArray;
	};

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Template for events with 3 arguments
 */
template <class T1 = EventNoArg, class T2 = EventNoArg, class T3 = EventNoArg>
class Event : public _REvent<MEventBase<T1, T2, T3>, MHandlerBase<T1, T2, T3> >
    {
    typedef _REvent<MEventBase<T1, T2, T3>, MHandlerBase<T1, T2, T3> > Base;

public:
    /**
     * From MEventBase3, operator ()
     */
    void operator ()(T1 aArg1, T2 aArg2, T3 aArg3);
    };

/**
 * Template partial specialization for events with no arguments.
 */
template <>
class Event<EventNoArg, EventNoArg, EventNoArg> : public _REvent<MEventBase<>, MHandlerBase<> >
    {
    typedef _REvent<MEventBase<>, MHandlerBase<> > Base;

public:
    /**
     * From MEventBase0, operator ()
     */
    IMPORT_C void operator ()();
    };

/**
 * Template partial specialization for events with 1 argument.
 */
template <class T1>
class Event<T1, EventNoArg, EventNoArg> : public _REvent<MEventBase<T1>, MHandlerBase<T1> >
    {
    typedef _REvent<MEventBase<T1>, MHandlerBase<T1> > Base;

public:
    /**
     * From MEventBase1, operator ()
     */
    void operator ()(T1 aArg1);
    };

/**
 * Template partial specialization for events with 2 arguments.
 */
template <class T1, class T2>
class Event<T1, T2, EventNoArg> : public _REvent<MEventBase<T1, T2>, MHandlerBase<T1, T2> >
    {
    typedef _REvent<MEventBase<T1, T2>, MHandlerBase<T1, T2> > Base;

public:
    /**
     * From MEventBase2, operator ()
     */
    void operator ()(T1 aArg1, T2 aArg2);
    };

#include "events.inl"

#endif //__EVENTS_H
