#include "painteventargs.h"

PaintEventArgs::PaintEventArgs(CBitmapContext& aGc, const TRect& aRect)
: _clipRectangle(aRect)
, _graphics(aGc)
    {
    // No implementation required
    }

PaintEventArgs::~PaintEventArgs()
    {
    // No implementation required
    }
