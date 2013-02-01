/*
 -------------------------------------------------------------------------------
 Name        : events.inl
 Author      : Marius Crisan
 Description : Events inlines and templates implementations.
 -------------------------------------------------------------------------------
 */

/**
 * Helper template function that appends an object into a pointer array.
 * @param aArray The array to append the object to.
 * @param aObject The object to append to array.
 */
template<class T>
void AppendL(RPointerArray<T>& aArray, const T* aObject)
    {
    aArray.AppendL(aObject);
    }

/**
 * Helper template function that removes an object from an array.
 * @param aArray The array to remove the object from.
 * @param aObject The object to remove.
 * @remarks First, the objects is searched by address. If it's not found, then it's searched
 * by polymorphic comparison between objects.
 */
template<class T>
void RemoveL(RPointerArray<T>& aArray, const T& aObject)
    {
    TInt pos = aArray.Find(&aObject);
    if (pos != KErrNotFound)
        {
        aArray.Remove(pos);
        }
    else
        {
        T* item = NULL;
        // Search for the handler and remove it
        for (TInt i = 0; i < aArray.Count() && (NULL == item); ++i)
            {
            if (aArray[i]->Equals(aObject))
                {
                item = aArray[i];
                aArray.Remove(i);
                }
            }
        if (NULL != item)
            {
            delete item;
            item = NULL;
            }
        }
    }

/**
 * _REvent::~_REvent
 * _REvent class template destructor.
 */
template<class EventBase, class HandlerBase>
_REvent<EventBase, HandlerBase>::~_REvent()
    {
    iHandlersArray.ResetAndDestroy();
    }

/**
 * _REvent::operator +=
 * Operator to add a handler.
 */
template<class EventBase, class HandlerBase>
EventBase& _REvent<EventBase, HandlerBase>::operator +=(const HandlerBase& aHandler)
    {
    AppendL(iHandlersArray, aHandler.CloneL());
    return *this;
    }

/**
 * _REvent::operator -=
 * Operator to remove a handler.
 */
template <class EventBase, class HandlerBase>
EventBase& _REvent<EventBase, HandlerBase>::operator -=(const HandlerBase& aHandler)
    {
    RemoveL(iHandlersArray, aHandler);
    return *this;
    }

/**
 * _REvent::operator TInt
 * Retrieves the number of handlers registered to this event.
 */
template <class EventBase, class HandlerBase>
_REvent<EventBase, HandlerBase>::operator TInt()
    {
    return iHandlersArray.Count();
    }

/**
 * Event::operator ()
 * Call operator for 3 arguments.
 */
template <class T1, class T2, class T3>
void Event<T1, T2, T3>::operator ()(T1 aArg1, T2 aArg2, T3 aArg3)
    {
    for (TInt i = 0; i < Base::iHandlersArray.Count(); ++i)
        {
        Base::iHandlersArray[i]->Call(aArg1, aArg2, aArg3);
        }
    }

/**
 * Event::operator ()
 * Call operator for 2 arguments.
 */
template <class T1, class T2>
void Event<T1, T2, EventNoArg>::operator ()(T1 aArg1, T2 aArg2)
    {
    for (TInt i = 0; i < Base::iHandlersArray.Count(); ++i)
        {
        Base::iHandlersArray[i]->Call(aArg1, aArg2);
        }
    }

/**
 * Event::operator ()
 * Call operator for 2 arguments.
 */
template <class T1>
void Event<T1, EventNoArg, EventNoArg>::operator ()(T1 aArg1)
    {
    for (TInt i = 0; i < Base::iHandlersArray.Count(); ++i)
        {
        Base::iHandlersArray[i]->Call(aArg1);
        }
    }

