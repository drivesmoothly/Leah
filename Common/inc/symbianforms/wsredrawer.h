#ifndef WSREDRAWER_H_
#define WSREDRAWER_H_

#include <e32base.h>

class WsClient;

class WsRedrawer : public CActive
    {
public: // Constructors and destructor
    WsRedrawer();
    ~WsRedrawer();
    void ConstructL(WsClient* aClient);

public: // New functions
    void IssueRequest();
    void DoCancel();
    void RunL();

protected: // Data
    WsClient* iClient;
    };

#endif //WSREDRAWER_H_
