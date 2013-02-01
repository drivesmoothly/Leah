
// ----------------------------------------------------------------------------
// PaintEventArgs::ClipRectangle
// Retrieves the clip rectangle.
// ----------------------------------------------------------------------------
//
const TRect& PaintEventArgs::ClipRectangle() const
    {
    return _clipRectangle;
    }

// ----------------------------------------------------------------------------
// PaintEventArgs::Graphics
// Retrieves the graphics context to draw to.
// ----------------------------------------------------------------------------
//
CBitmapContext& PaintEventArgs::Graphics()
    {
    return _graphics;
    }
