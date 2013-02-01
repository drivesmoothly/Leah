#include "LeahServiceEngine.h"

CLeahServiceEngine* CLeahServiceEngine::NewL(CLeahServiceServer& aServer)
	{
	CLeahServiceEngine* self = CLeahServiceEngine::NewLC(aServer);
	CleanupStack::Pop(self);
	return self;
	}

CLeahServiceEngine* CLeahServiceEngine::NewLC(CLeahServiceServer& aServer)
	{
	CLeahServiceEngine* self = new (ELeave) CLeahServiceEngine(aServer);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLeahServiceEngine::~CLeahServiceEngine()
	{
	
	}

CLeahServiceEngine::CLeahServiceEngine(CLeahServiceServer& aServer)
: iServer(aServer)
	{
	
	}

void CLeahServiceEngine::ConstructL()
	{
	
	}

void CLeahServiceEngine::SaveSettingsL()
	{
	
	}

void CLeahServiceEngine::LoadSettingsL()
	{
	
	}
