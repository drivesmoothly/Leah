#include "backbuffer.h"
#include <bitstd.h>
#include <bitdev.h>

EXPORT_C BackBuffer::BackBuffer()
: Bitmap(*this, &BackBuffer::GetBitmap)
, Gc(*this, &BackBuffer::GetGc)
    {
    User::LeaveIfError(iWsSession.Connect());
    }

EXPORT_C BackBuffer::~BackBuffer()
    {
    Close();
    iWsSession.Close();
    }

EXPORT_C void BackBuffer::Create(const TSize& aSize)
    {
    ASSERT(!iBackBuffer);
    ASSERT(!iDevice);
    ASSERT(!iGc);
    iBackBuffer = new (ELeave) CWsBitmap(iWsSession);
    User::LeaveIfError(iBackBuffer->Create(aSize, EColor16MA));
    iDevice = CFbsBitmapDevice::NewL(iBackBuffer);
    User::LeaveIfError(iDevice->CreateContext(iGc));
    iGc->SetDrawMode(CGraphicsContext::EDrawModeWriteAlpha);
    }

EXPORT_C void BackBuffer::Close()
    {
    delete iGc;
    iGc = NULL;
    delete iDevice;
    iDevice = NULL;
    delete iBackBuffer;
    iBackBuffer = NULL;
    }

EXPORT_C void BackBuffer::Resize(const TSize& aSize)
    {
    ASSERT(iBackBuffer);
    ASSERT(iDevice);
    User::LeaveIfError(iBackBuffer->Resize(aSize));
    User::LeaveIfError(iDevice->Resize(aSize));
    iGc->Resized();
    }

CWsBitmap* BackBuffer::GetBitmap() const
    {
    return iBackBuffer;
    }

CFbsBitGc* BackBuffer::GetGc() const
    {
    return iGc;
    }
