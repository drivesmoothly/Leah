
const CLeahServiceEngine& CLeahServiceServer::Engine() const
    {
    ASSERT(iEngine);
    return *iEngine;
    }

CLeahServiceEngine& CLeahServiceServer::Engine()
    {
    ASSERT(iEngine);
    return *iEngine;
    }

RPointerArray<CLeahServiceSession> CLeahServiceServer::Sessions()
	{
	return iSessions;
	}

void CLeahServiceServer::SetToExit(TBool aExit)
    {
    iExitWhenNoSessions = aExit;
    }

TBool CLeahServiceServer::IsSetToExit() const
    {
    return iExitWhenNoSessions;
    }

TBool CLeahServiceServer::AutoStarted() const
    {
    return iAutoStarted;
    }

void CLeahServiceServer::SetAutoStarted(TBool aAutoStarted)
    {
    iAutoStarted = aAutoStarted;
    }
