#ifndef PAINTEVENTARGS_H_
#define PAINTEVENTARGS_H_

#include "property.h"

class CBitmapContext;

class PaintEventArgs
    {
public: // Constructors and destructor
    PaintEventArgs(CBitmapContext& aGc, const TRect& aRect);
    ~PaintEventArgs();

public: // New functions
    inline const TRect& ClipRectangle() const;
    inline CBitmapContext& Graphics();

private: // Data
    TRect _clipRectangle;
    CBitmapContext& _graphics;
    };

#include "painteventargs.inl"

#endif //PAINTEVENTARGS_H_
