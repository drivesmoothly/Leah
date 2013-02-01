#ifndef LEAHSERVICESERVER_H_
#define LEAHSERVICESERVER_H_

#include <e32base.h>
#include "LeahServiceInterface.h"

class CLeahServiceSession;
class CLeahServiceEngine;

class CLeahServiceServer : public CServer2
    {
    friend class CLeahServiceEngine;
    friend class CLeahServiceSession;

public:
    static CLeahServiceServer* NewL(CActiveSchedulerWait& aWait, TBool aAutostarted);
    static CLeahServiceServer* NewLC(CActiveSchedulerWait& aWait, TBool aAutostarted);
    virtual ~CLeahServiceServer();

protected:
    CLeahServiceServer(CActiveSchedulerWait& aWait, TInt aPriority, TBool aAutostarted);
    void ConstructL();

public:
    static TInt ThreadFunction(TAny* aNone);

    void SessionCreatedL(CLeahServiceSession* aSession);
    void SessionEnded(CLeahServiceSession* aSession);

    inline const CLeahServiceEngine& Engine() const;

    inline void SetToExit(TBool aExit);
    inline TBool IsSetToExit() const;

    void NotifyClientObservers(TLeahServiceObserverEvent aEvent);

    inline TBool AutoStarted() const;
    inline void SetAutoStarted(TBool aAutoStarted);

    void TestHandler0(){}
    void TestHandler1(TInt){}
    void TestHandler2(TInt, TInt){}
    void TestHandler3(TInt, TInt, TInt){}

private:
    static void ThreadFunctionL();

protected: // From base classes
    CSession2* NewSessionL(const TVersion& aVersion, const RMessage2& aMessage) const;
    void Stop();

    inline CLeahServiceEngine& Engine();
    inline RPointerArray<CLeahServiceSession> Sessions();

private:
    CActiveSchedulerWait& iWait;
    CLeahServiceEngine* iEngine;

    TBool iExitWhenNoSessions;
    mutable RPointerArray<CLeahServiceSession> iSessions;

    TBool iAutoStarted;
    };

#include "LeahServiceServer.inl"

#endif //LEAHSERVICESERVER_H_
