#include "LeahServiceServer.h"
#include "LeahServiceEngine.h"
#include "LeahServiceSession.h"
#include "LeahConsts.h"
#include "LeahServiceCommon.h"
#include "LeahSettings.h"

#include "property.h"

CLeahServiceServer* CLeahServiceServer::NewL(CActiveSchedulerWait& aWait,
		TBool aAutostarted)
	{
	CLeahServiceServer* self = CLeahServiceServer::NewLC(aWait, aAutostarted);
	CleanupStack::Pop(self);
    return self;
	}

CLeahServiceServer* CLeahServiceServer::NewLC(CActiveSchedulerWait& aWait,
		TBool aAutostarted)
	{
	CLeahServiceServer* self = new (ELeave) CLeahServiceServer(aWait,
			EPriorityStandard, aAutostarted);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLeahServiceServer::~CLeahServiceServer()
	{
	delete iEngine;
	Sessions().Reset();
	}

CLeahServiceServer::CLeahServiceServer(CActiveSchedulerWait& aWait,
		TInt aPriority, TBool aAutostarted) :
	CServer2(aPriority), iWait(aWait), iExitWhenNoSessions(EFalse),
			iAutoStarted(aAutostarted)
	{
	}

void CLeahServiceServer::ConstructL()
	{
	StartL(KLeahServiceServerName);
	iEngine = CLeahServiceEngine::NewL(*this);
	}

TInt CLeahServiceServer::ThreadFunction(TAny* /*aNone*/)
	{
	__UHEAP_MARK;

	RThread::RenameMe(KLeahServiceServerName);

	CTrapCleanup* cleanupStack = CTrapCleanup::New();
	if (!cleanupStack)
		{
		PanicServer(KErrAbort);
		}

	TRAPD(err, ThreadFunctionL());

	delete cleanupStack;
	cleanupStack = NULL;

	__UHEAP_MARKEND;
	return KErrNone;
	}

void CLeahServiceServer::SessionCreatedL(CLeahServiceSession* aSession)
	{
	Sessions().AppendL(aSession);
	}

void CLeahServiceServer::SessionEnded(CLeahServiceSession* aSession)
    {
    TInt findPos = Sessions().Find(aSession);
    if (findPos != KErrNotFound)
        {
        Sessions().Remove(findPos);
        }
    if (!Sessions().Count() && IsSetToExit())
        {
        Stop();
        }
    }

void CLeahServiceServer::ThreadFunctionL()
	{
	CActiveScheduler* activeScheduler = new (ELeave) CActiveScheduler();
	CleanupStack::PushL(activeScheduler);
	CActiveScheduler::Install(activeScheduler);

	CActiveSchedulerWait* wait = new (ELeave) CActiveSchedulerWait();
	CleanupStack::PushL(wait);

	RSemaphore semaphore;
	CleanupClosePushL(semaphore);
	TBool autoStarted = ~(KErrNone == semaphore.OpenGlobal(KLeahServiceSemaphoreName));

	CLeahServiceServer* server = CLeahServiceServer::NewL(*wait, autoStarted);
	if (!autoStarted)
		{
		semaphore.Signal();
		}
	CleanupStack::PopAndDestroy(&semaphore);
	CleanupStack::PushL(server);

	if (!autoStarted || server->Engine().Settings().Autostart())
		{
		wait->Start();
		}
	CleanupStack::PopAndDestroy(3, activeScheduler);
	}


CSession2* CLeahServiceServer::NewSessionL(const TVersion& aVersion,
        const RMessage2& /*aMessage*/) const
	{
	if (!User::QueryVersionSupported(TVersion(KLeahServiceVersionMajor,
	            KLeahServiceVersionMinor, KLeahServiceVersionBuild), aVersion))
	        {
	        User::Leave(KErrNotSupported);
	        }
	    CLeahServiceSession* session = CLeahServiceSession::NewL(
	            *const_cast<CLeahServiceServer*> (this));
	    return session;
	}

void CLeahServiceServer::NotifyClientObservers(TLeahServiceObserverEvent aEvent)
    {
    for (TInt i = 0; i < Sessions().Count(); ++i)
        {
        Sessions()[i]->NotifyClientObserver(aEvent);
        }
    }

void CLeahServiceServer::Stop()
    {
    iWait.AsyncStop();
    }
