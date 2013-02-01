#ifndef BACKBUFFER_H_
#define BACKBUFFER_H_

#include <w32std.h>
#include "property.h"

class CWsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;

class BackBuffer : public CBase
    {
public: // Properties
    PropertyReadExt<CWsBitmap*, BackBuffer> Bitmap;
    PropertyReadExt<CFbsBitGc*, BackBuffer> Gc;

public: // Constructors and destructors
    IMPORT_C BackBuffer();
    IMPORT_C ~BackBuffer();

public: // New functions
    IMPORT_C void Create(const TSize& aSize);
    IMPORT_C void Close();
    IMPORT_C void Resize(const TSize& aSize);

protected: // New functions
    CWsBitmap* GetBitmap() const;
    CFbsBitGc* GetGc() const;

protected: // Data
    CWsBitmap* iBackBuffer;
    CFbsBitmapDevice* iDevice;
    CFbsBitGc* iGc;
    RWsSession iWsSession;
    };

#endif //BACKBUFFER_H_
