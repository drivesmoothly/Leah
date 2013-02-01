#ifndef IMAGE_H_
#define IMAGE_H_

// SYSTEM INCLUDES
#include <gdi.h>

// USER INCLUDES
#include "control.h"
#include "align.h"

// FORWARDS
class CFbsBitmap;

/**
 * Image class.
 * Responsible for presenting an image in the UI.
 */
class Image : public Control
    {
public: // PROPERTIES
    Property<Alignment::Align> Align;
    PropertyDes Path;
    Property<TRgb> BackgroundColor;
    Property<TInt> CornerRadius;
    Property<TInt> BorderSize;
    Property<TRgb> BorderColor;

public: // CONSTRUCTORS AND DESTRUCTORS
    IMPORT_C Image();
    IMPORT_C ~Image();

public: // FROM BASE CLASS
    IMPORT_C void OnPaint(PaintEventArgs& aArgs);
    /**
     * From Control, Measure.
     * @param aAvailableSize The available size.
     * @return The necessary size for the control.
     */
    TSize Measure(const TSize& aAvailableSize);
    /**
     * From Control, Arrange.
     * @param aFinalSize The final available size.
     * @return The size occupied by the control.
     */
    TSize Arrange(const TSize& aFinalSize);
    /**
     * Sets the bitmap and mask. Image control does not take ownership.
     * @param aBitmap The bitmap.
     * @param aMask The mask.
     */
    void SetBitmap(const CFbsBitmap* aBitmap, const CFbsBitmap* aMask = NULL);
    /**
     * Sets the bitmap from the image store, based on the given id.
     * @param aImageId The image id from the image store.
     */
    void SetBitmapId(TInt aImageId);

protected: // NEW FUNCTIONS
    void Align_Changed(const PropertyBase<Alignment::Align>& Align);
    void Path_Changed(const PropertyBase<const TDesC&>& aPath);
    void BackgroundColor_Changed(const PropertyBase<TRgb>& aBackColor);
    void CornerRadius_Changed(const PropertyBase<TInt>& aCornerRadius);
    void BorderSize_Changed(const PropertyBase<TInt>& aBorderSize);
    void BorderColor_Changed(const PropertyBase<TRgb>& aBorderColor);
    void ClientRect_Changed(const PropertyBase<TRect>& aClientRect);

private: // New functions
    void CloseBitmapId();

private: // DATA
    TPoint _imagePosition;
    CFbsBitmap* _image;
    CFbsBitmap* _mask;
    const CFbsBitmap* _displayBitmap;
    const CFbsBitmap* _displayMask;
    TInt _bitmapId;
    };

#endif //IMAGE_H_
