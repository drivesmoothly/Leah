#include "wsredrawer.h"
#include "wsclient.h"
#include "form.h"

WsRedrawer::WsRedrawer()
: CActive(CActive::EPriorityIdle)
    {
    // No implementation required
    }

WsRedrawer::~WsRedrawer()
    {
    Cancel();
    }

void WsRedrawer::ConstructL(WsClient* aClient)
    {
    iClient = aClient;
    iClient->WsSession->SetAutoFlush(ETrue);
    CActiveScheduler::Add(this);
    IssueRequest();
    }

void WsRedrawer::IssueRequest()
    {
    iClient->WsSession().RedrawReady(&iStatus);
    SetActive();
    }

void WsRedrawer::DoCancel()
    {
    iClient->WsSession().RedrawReadyCancel();
    }

void WsRedrawer::RunL()
    {
    TWsRedrawEvent redrawEvent;
    iClient->WsSession().GetRedraw(redrawEvent);

    Form* form = (Form*)(redrawEvent.Handle());
    if (form)
        {
        TRect rect = redrawEvent.Rect();
        RWindow& formWindow = *form->Window;
        CWindowGc& clientGc = iClient->Gc;

        clientGc.Activate(formWindow);
        formWindow.BeginRedraw(rect);

        PaintEventArgs args(clientGc, rect);
        form->RaisePaintEvent(form, args);

        formWindow.EndRedraw();
        clientGc.Deactivate();
        }

    IssueRequest();
    }
