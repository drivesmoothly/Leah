// USER INCLUDES
#include "image.h"
#include "handlermethod.h"
#include "imageloader.h"
#include "numericutils.h"
#include "imagestore.h"

// SYSTEM INCLUDES
#include <fbs.h>

// ----------------------------------------------------------------------------
// Image::Image
// Image class constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C Image::Image()
: BackgroundColor(TRgb(0, 0, 0, 0))
, CornerRadius(5)
, BorderSize(0)
, BorderColor(TRgb(100, 100, 100))
, _bitmapId(ImageStore::EBitmapIdNone)
    {
    Align.ValueChanged += MethodHandler(this, &Image::Align_Changed);
    Path.ValueChanged += MethodHandler(this, &Image::Path_Changed);
    BackgroundColor.ValueChanged += MethodHandler(this, &Image::BackgroundColor_Changed);
    CornerRadius.ValueChanged += MethodHandler(this, &Image::CornerRadius_Changed);
    BorderSize.ValueChanged += MethodHandler(this, &Image::BorderSize_Changed);
    BorderColor.ValueChanged += MethodHandler(this, &Image::BorderColor_Changed);
    ClientRectangle.ValueChanged += MethodHandler(this, &Image::ClientRect_Changed);
    }

// ----------------------------------------------------------------------------
// Image::~Image
// Image class destructor.
// ----------------------------------------------------------------------------
//
EXPORT_C Image::~Image()
    {
    CloseBitmapId();
    delete _image;
    delete _mask;
    }

// ----------------------------------------------------------------------------
// Image::OnPaint
// Override from Control. Draws the image to the UI.
// ----------------------------------------------------------------------------
//
EXPORT_C void Image::OnPaint(PaintEventArgs& aArgs)
    {
    CBitmapContext& gc = aArgs.Graphics();
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(BackgroundColor);
    if (BorderSize > 0)
        {
        gc.SetPenStyle(CGraphicsContext::ESolidPen);
        gc.SetPenColor(BorderColor);
        gc.SetPenSize(TSize(BorderSize, BorderSize));
        }
    else
        {
        gc.SetPenStyle(CGraphicsContext::ENullPen);
        }
    gc.DrawRoundRect(ClientRectangle, TSize(CornerRadius, CornerRadius));

    if (_displayBitmap && _displayMask)
        {
        gc.BitBltMasked(_imagePosition, _displayBitmap, TRect(_displayBitmap->SizeInPixels()), _displayMask, ETrue);
        }
    else if (_displayBitmap)
        {
        gc.BitBlt(_imagePosition, _displayBitmap);
        }
    Control::OnPaint(aArgs);
    }

// ----------------------------------------------------------------------------
// Image::Measure
// From Control, Measure. Measures the necessary size for the control.
// ----------------------------------------------------------------------------
//
TSize Image::Measure(const TSize& aAvailableSize)
    {
    TSize preferredSize(0, 0);
    if (_displayBitmap)
        {
        preferredSize = _displayBitmap->SizeInPixels();
        // Correct aspect ratio
        if (preferredSize.iWidth > aAvailableSize.iWidth || preferredSize.iHeight > aAvailableSize.iHeight)
            {
            TReal scaleFactor = Min(((TReal)aAvailableSize.iWidth) / preferredSize.iWidth,
                    ((TReal)aAvailableSize.iHeight) / preferredSize.iHeight);
            preferredSize = NumericUtils::ScaleSize(preferredSize, scaleFactor);
            }
        }
    PreferredSize = preferredSize;
    return preferredSize;
    }

// ----------------------------------------------------------------------------
// Image::Arrange
// From Control, Arrange. Arranges the control into the given size.
// ----------------------------------------------------------------------------
//
TSize Image::Arrange(const TSize& aFinalSize)
    {
    if (_displayBitmap)
        {
        TSize imageSize = _displayBitmap->SizeInPixels();
        TRect clientRect = ClientRectangle;
        _imagePosition = DoAlign(Align, clientRect.Size(), imageSize);
        _imagePosition += clientRect.iTl;
        }
    return aFinalSize;
    }

// ----------------------------------------------------------------------------
// Image::SetBitmap
// Sets a bitmap and a mask.
// ----------------------------------------------------------------------------
//
void Image::SetBitmap(const CFbsBitmap* aBitmap, const CFbsBitmap* aMask)
    {
    CloseBitmapId();
    _displayBitmap = aBitmap;
    _displayMask = aMask;
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Image::SetBitmapId
// Sets the bitmap based on an id from the image store.
// ----------------------------------------------------------------------------
//
void Image::SetBitmapId(TInt aBitmapId)
    {
    if (aBitmapId == _bitmapId)
        {
        return;
        }

    CloseBitmapId();
    _bitmapId = aBitmapId;
    ImageStore::Instance().UseImage(_bitmapId, _displayBitmap, _displayMask);
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Image::Align_Changed
// Handler for Align property change.
// ----------------------------------------------------------------------------
//
void Image::Align_Changed(const PropertyBase<Alignment::Align>& /*aAlign*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Image::Path_Changed
// Handler for Path property change.
// ----------------------------------------------------------------------------
//
void Image::Path_Changed(const PropertyBase<const TDesC&>& /*aPath*/)
    {
    ImageLoader::LoadImageL(Path, _image, _mask);
    SetBitmap(_image, _mask);
    }

// ----------------------------------------------------------------------------
// Image::BackgroundColor_Changed
// Handler for BackgroundColor property change.
// ----------------------------------------------------------------------------
//
void Image::BackgroundColor_Changed(const PropertyBase<TRgb>& /*aBackColor*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Image::CornerRadius_Changed
// Handler for CornerRadius property change.
// ----------------------------------------------------------------------------
//
void Image::CornerRadius_Changed(const PropertyBase<TInt>& /*aCornerRadius*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Image::BorderSize_Changed
// Handler for BorderSize property change.
// ----------------------------------------------------------------------------
//
void Image::BorderSize_Changed(const PropertyBase<TInt>& /*aBorderSize*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Image::BorderColor_Changed
// Handler for BorderColor property change.
// ----------------------------------------------------------------------------
//
void Image::BorderColor_Changed(const PropertyBase<TRgb>& /*aBorderColor*/)
    {
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Image::ClientRect_Changed
// Handler for ClientRectangle property change.
// ----------------------------------------------------------------------------
//
void Image::ClientRect_Changed(const PropertyBase<TRect>& /*aBorderColor*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// Image::CloseBitmapId
// Closes the bitmap id. Calls ImageStore::Release
// ----------------------------------------------------------------------------
//
void Image::CloseBitmapId()
    {
    if (_bitmapId != ImageStore::EBitmapIdNone)
        {
        ImageStore::Instance().ReleaseImage(_bitmapId);
        _bitmapId = ImageStore::EBitmapIdNone;
        }
    }
