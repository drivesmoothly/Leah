/*
 ===============================================================================
 Name        : asynccommandhandler.inl
 Author      : Marius Crisan
 Description : Async command handler class template.
 ===============================================================================
 */

template <class T>
RAsyncCommandHandler<T>::RAsyncCommandHandler()
:   iPostCommandIdle(NULL)
,   iFromCallback(EFalse)
    {
    // No implementation required
    }

template <class T>
RAsyncCommandHandler<T>::~RAsyncCommandHandler()
    {
    iCommandsArray.Reset();
    delete iPostCommandIdle;
    }

template <class T>
void RAsyncCommandHandler<T>::PostCommandL(const T& aCommand) const
    {
    iCommandsArray.AppendL(aCommand);
    if (!iFromCallback)
        StartCommandQueueTimerL();
    }

template <class T>
TBool RAsyncCommandHandler<T>::CommandsQueueEmpty() const
    {
    return ( iCommandsArray.Count() == 0 );
    }

template <class T>
TBool RAsyncCommandHandler<T>::CommandPosted(const T& aCommand) const
    {
    return (iCommandsArray.Find(aCommand) != KErrNotFound);
    }

template <class T>
void RAsyncCommandHandler<T>::StartCommandQueueTimerL() const
    {
    if (!iPostCommandIdle)
        iPostCommandIdle = CIdle::NewL(CIdle::EPriorityIdle);

    if (!iPostCommandIdle->IsActive())
        iPostCommandIdle->Start(TCallBack(PostCommandCallback, (TAny*)this));
    }

template <class T>
void RAsyncCommandHandler<T>::StopCommandQueueTimer()
    {
    if (iPostCommandIdle)
        iPostCommandIdle->Cancel();
    }

template <class T>
TInt RAsyncCommandHandler<T>::PostCommandCallback(TAny* aPtr)
    {
    TBool returnValue = ETrue;

    RAsyncCommandHandler<T>* self = (RAsyncCommandHandler<T>*) aPtr;
    self->iFromCallback = ETrue;

    if (self->iCommandsArray.Count())
    {
        self->AsyncHandleCommandL(self->iCommandsArray[0]);
        self->iCommandsArray.Remove(0);
    }
    if ( self->CommandsQueueEmpty() )
    {
        // Do not continue
        returnValue = EFalse;
    }
    self->iFromCallback = EFalse;
    return returnValue;
    }

// ----------------------------------------------------------------------------
// T*
// ----------------------------------------------------------------------------

template <class T>
RAsyncCommandHandler<T*>::RAsyncCommandHandler()
:   iPostCommandIdle(NULL)
,   iFromCallback(EFalse)
    {
        // No implementation required
    }

template <class T>
RAsyncCommandHandler<T*>::~RAsyncCommandHandler()
    {
    iCommandsArray.ResetAndDestroy();
    delete iPostCommandIdle;
    }

template <class T>
void RAsyncCommandHandler<T*>::PostCommandL(T* aCommand) const
    {
    iCommandsArray.AppendL(aCommand);
    if (!iFromCallback)
        StartCommandQueueTimerL();
    }

template <class T>
TBool RAsyncCommandHandler<T*>::CommandsQueueEmpty() const
    {
    return ( iCommandsArray.Count() == 0 );
    }

template <class T>
TBool RAsyncCommandHandler<T*>::CommandPosted(T* aCommand) const
    {
    return (iCommandsArray.Find(aCommand) != KErrNotFound);
    }

template <class T>
void RAsyncCommandHandler<T*>::StartCommandQueueTimerL() const
    {
    if (!iPostCommandIdle)
        iPostCommandIdle = CIdle::NewL(CIdle::EPriorityHigh);

    if (!iPostCommandIdle->IsActive())
        iPostCommandIdle->Start(TCallBack(PostCommandCallback, (TAny*)this));
    }

template <class T>
void RAsyncCommandHandler<T*>::StopCommandQueueTimer()
    {
    if (iPostCommandIdle)
        iPostCommandIdle->Cancel();
    }

template <class T>
TInt RAsyncCommandHandler<T*>::PostCommandCallback(TAny* aPtr)
{
    TBool returnValue = ETrue;

    RAsyncCommandHandler<T>* self = (RAsyncCommandHandler<T>*) aPtr;
    self->iFromCallback = ETrue;

    if (self->iCommandsArray.Count())
    {
        self->AsyncHandleCommandL(self->iCommandsArray[0]);
        delete self->iCommandsArray[0];
        self->iCommandsArray.Remove(0);
    }
    if ( self->CommandsQueueEmpty() )
    {
        returnValue = EFalse;
    }
    self->iFromCallback = EFalse;
    return returnValue;
}
