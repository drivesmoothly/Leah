#include "LeahServiceEntry.h"
#include "LeahServiceServer.h"

TInt E32Main()
    {
    return CLeahServiceServer::ThreadFunction(NULL);
    }
