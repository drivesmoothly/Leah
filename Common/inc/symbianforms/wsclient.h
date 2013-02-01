#ifndef WSCLIENT_H_
#define WSCLIENT_H_

#include <e32base.h>
#include <w32std.h>
#include "property.h"
#include "events.h"

class WsRedrawer;
class CWsScreenDevice;
class CApaWindowGroupName;

class WsClient : public CActive
    {
public: // Events
    Event<TWsEvent&> WsEvent;

public: // Properties
    PropertyReadExt<CWsScreenDevice&, WsClient> Screen;
    PropertyReadExt<CWindowGc&, WsClient> Gc;
    PropertyReadExt<RWsSession&, WsClient> WsSession;
    PropertyReadExt<RWindowGroup&, WsClient> WindowGroup;

public: // Constructors and destructor
    WsClient(const TUid& aAppUid);
    ~WsClient();

    void ConstructL();

public: // New functions
    void Destroy();
    void IssueRequest();
    /**
     * Retrieves the screen size.
     * @return The screen size.
     */
    TSize ScreenSize();

public: // From CActive
    void DoCancel();
    void RunL();

protected: // New functions
    CWsScreenDevice& GetScreenDevice() const;
    CWindowGc& GetGc() const;
    RWsSession& GetWsSession() const;
    RWindowGroup& GetWindowGroup() const;

private: // Data
    CWsScreenDevice* iScreen;
    TWsEvent iWsEvent;
    CWindowGc* iGc;
    CApaWindowGroupName* iWgName;
    TUid iAppUid;
    mutable RWindowGroup iGroup;
    mutable RWsSession iWs;
    };

#endif //WSCLIENT_H_
