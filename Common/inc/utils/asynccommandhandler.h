/*
 ===============================================================================
 Name        : asynccommandhandler.h
 Author      : Marius Crisan
 Description : Async command handler class template.
 ===============================================================================
 */

#ifndef __ASYNCCOMMANDHANDLER_H
#define __ASYNCCOMMANDHANDLER_H

#include <e32std.h>
#include <e32base.h>

/**
 * Template for asynchronous commands handling.
 * Non pointer version
 */
template <class T>
class RAsyncCommandHandler
{
protected:

    /**
     * Called to handle a command.
     * @param aCommand The command to handle.
     */
    virtual void AsyncHandleCommandL(const T& aCommand) = 0;

public:
    /**
     * C++ constructor.
     */
    RAsyncCommandHandler();
    /**
     * Destructor.
     */
    virtual ~RAsyncCommandHandler();

    /**
     * Adds a command in queue to schedule execution.
     * @param aCommand The command to add in queue.
     */
    void PostCommandL(const T& aCommand) const;

    /**
     * Checks if the commands queue is empty.
     * @return ETrue if it's empty, EFalse otherwise.
     */
    inline TBool CommandsQueueEmpty() const;

    /**
     * Checks if a given command already exists in queue.
     * @param aCommand The command to search for.
     * @return ETrue if already posted, EFalse if not.
     */
    inline TBool CommandPosted(const T& aCommand) const;

private:
    /**
     * Starts the idle for performing asynchronous commands.
     */
    void StartCommandQueueTimerL() const;

    /**
     * Stops the idle for performing asynchronous commands.
     */
    void StopCommandQueueTimer();

    /**
     * Static callback for the commands post idle.
     */
    static TInt PostCommandCallback(TAny* aPtr);

private:
    /**
     * The commands array.
     */
    mutable RArray<T> iCommandsArray;
    /**
     * The idle timer.
     */
    mutable CIdle* iPostCommandIdle;
    /**
     * Internal. Stores if the PostCommandL was called from the callback.
     */
    TBool iFromCallback;
};

/**
 * Template for asynchronous commands handling.
 * Pointer version
 */
template <class T>
class RAsyncCommandHandler<T*>
{
public:
    RAsyncCommandHandler();

    virtual ~RAsyncCommandHandler();

    void PostCommandL(T* aCommand) const;

    /**
     * Checks if the commands queue is empty.
     * @return ETrue if it's empty, EFalse otherwise.
     */
    inline TBool CommandsQueueEmpty() const;

    /**
     * Checks if a given command already exists in queue.
     * @param aCommand The command to search for.
     * @return ETrue if already posted, EFalse if not.
     */
    inline TBool CommandPosted(T* aCommand) const;

protected:
    virtual void AsyncHandleCommandL(T* aCommand) = 0;

private:
    /**
     * Starts the idle for performing asynchronous commands.
     */
    void StartCommandQueueTimerL() const;

    /**
     * Stops the idle for performing asynchronous commands.
     */
    void StopCommandQueueTimer();

    /**
     * Static callback for the commands post idle.
     */
    static TInt PostCommandCallback(TAny* aPtr);

private:
    mutable RPointerArray<T> iCommandsArray;
    mutable CIdle* iPostCommandIdle;
    TBool iFromCallback;
};

#include "asynccommandhandler.inl"

#endif //__ASYNCCOMMANDHANDLER_H
