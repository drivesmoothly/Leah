#include "LeahServiceSession.h"
#include "LeahServiceServer.h"

CLeahServiceSession* CLeahServiceSession::NewL(CLeahServiceServer& aServer)
	{
	CLeahServiceSession* self = CLeahServiceSession::NewLC(aServer);
	CleanupStack::Pop(self);
	return self;
	}

CLeahServiceSession* CLeahServiceSession::NewLC(CLeahServiceServer& aServer)
	{
	CLeahServiceSession* self = new (ELeave) CLeahServiceSession(aServer);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLeahServiceSession::~CLeahServiceSession()
	{
	Server().SessionEnded(this);
	}

void CLeahServiceSession::ServiceL(const RMessage2& aMessage)
	{
	aMessage.Complete(KErrNone);
	}

void CLeahServiceSession::NotifyClientObserver(TLeahServiceObserverEvent /*aEvent*/)
	{

	}

const CLeahServiceEngine& CLeahServiceSession::Engine() const
	{
	return Server().Engine();
	}

CLeahServiceSession::CLeahServiceSession(CLeahServiceServer& aServer)
: iServer(aServer)
	{

	}

void CLeahServiceSession::ConstructL()
	{
	Server().SessionCreatedL(this);
	}

CLeahServiceEngine& CLeahServiceSession::Engine()
	{
	return Server().Engine();
	}
