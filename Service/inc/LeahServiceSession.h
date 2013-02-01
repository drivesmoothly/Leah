#ifndef LEAHSERVICESESSION_H_
#define LEAHSERVICESESSION_H_

#include <e32base.h>

#include "LeahServiceInterface.h"

class CLeahServiceEngine;
class CLeahServiceServer;

class CLeahServiceSession : public CSession2
    {
public:
    static CLeahServiceSession* NewL(CLeahServiceServer& aServer);
    static CLeahServiceSession* NewLC(CLeahServiceServer& aServer);
    virtual ~CLeahServiceSession();

public: // From base class
    void ServiceL(const RMessage2& aMessage);
    void NotifyClientObserver(TLeahServiceObserverEvent aEvent);

    const CLeahServiceEngine& Engine() const;
    inline const CLeahServiceServer& Server() const;

protected:
    CLeahServiceSession(CLeahServiceServer& aServer);
    void ConstructL();

    CLeahServiceEngine& Engine();
    inline CLeahServiceServer& Server();

private:
    CLeahServiceServer& iServer;
    RMessage2 iObserverMessage;
    };

#include "LeahServiceSession.inl"

#endif //LEAHSERVICESESSION_H_
