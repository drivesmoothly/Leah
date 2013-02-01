#include "propertyadapters.h"

/// ---------------------------------------------------------------------------
/// From TRect to components
/// ---------------------------------------------------------------------------

EXPORT_C void PropertyAdapters::FromRectToTop(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aTop)
    {
    aTop = aRect().iTl.iY;
    }

EXPORT_C void PropertyAdapters::FromRectToLeft(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aLeft)
    {
    aLeft = aRect().iTl.iX;
    }

EXPORT_C void PropertyAdapters::FromRectToBottom(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aBottom)
    {
    aBottom = aRect().iBr.iY;
    }

EXPORT_C void PropertyAdapters::FromRectToRight(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aRight)
    {
    aRight = aRect().iBr.iX;
    }

EXPORT_C void PropertyAdapters::FromRectToLocation(const PropertyBase<TRect>& aRect, PropertyBase<TPoint>& aLocation)
    {
    aLocation = aRect().iTl;
    }

EXPORT_C void PropertyAdapters::FromRectToSize(const PropertyBase<TRect>& aRect, PropertyBase<TSize>& aSize)
    {
    aSize = aRect().Size();
    }

EXPORT_C void PropertyAdapters::FromRectToHeight(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aHeight)
    {
    aHeight = aRect().Height();
    }

EXPORT_C void PropertyAdapters::FromRectToWidth(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aWidth)
    {
    aWidth = aRect().Width();
    }

EXPORT_C void PropertyAdapters::FromRectToBottomRight(const PropertyBase<TRect>& aRect, PropertyBase<TPoint>& aBottomRight)
    {
    aBottomRight = aRect().iBr;
    }

EXPORT_C void PropertyAdapters::FromAlignmentToHAlignment(const PropertyBase<Alignment::Align>& aAlignment,
        PropertyBase<HAlignment::Align>& aHAlign)
    {
    aHAlign = GetHAlignment(aAlignment);
    }

EXPORT_C void PropertyAdapters::FromAlignmentToVAlignment(const PropertyBase<Alignment::Align>& aAlignment,
        PropertyBase<VAlignment::Align>& aVAlign)
    {
    aVAlign = GetVAlignment(aAlignment);
    }

/// ---------------------------------------------------------------------------
/// From components to TRect
/// ---------------------------------------------------------------------------

EXPORT_C void PropertyAdapters::FromTopToRect(const PropertyBase<TInt>& aTop, PropertyBase<TRect>& aRect)
    {
    TRect rect(TPoint(aRect().iTl.iX, aTop), aRect().Size());
    aRect = rect;
    }

EXPORT_C void PropertyAdapters::FromLeftToRect(const PropertyBase<TInt>& aLeft, PropertyBase<TRect>& aRect)
    {
    TRect rect(TPoint(aLeft, aRect().iTl.iY), aRect().Size());
    aRect = rect;
    }

EXPORT_C void PropertyAdapters::FromBottomToRect(const PropertyBase<TInt>& aBottom, PropertyBase<TRect>& aRect)
    {
    TRect rect(aRect().iTl, TPoint(aRect().iBr.iX, aBottom));
    aRect = rect;
    }

EXPORT_C void PropertyAdapters::FromRightToRect(const PropertyBase<TInt>& aRight, PropertyBase<TRect>& aRect)
    {
    TRect rect(aRect().iTl, TPoint(aRight, aRect().iBr.iY));
    aRect = rect;
    }

EXPORT_C void PropertyAdapters::FromLocationToRect(const PropertyBase<TPoint>& aLocation, PropertyBase<TRect>& aRect)
    {
    TRect rect(aLocation, aRect().Size());
    aRect = rect;
    }

EXPORT_C void PropertyAdapters::FromSizeToRect(const PropertyBase<TSize>& aSize, PropertyBase<TRect>& aRect)
    {
    TRect rect(aRect().iTl, aSize);
    aRect = rect;
    }

EXPORT_C void PropertyAdapters::FromWidthToRect(const PropertyBase<TInt>& aWidth, PropertyBase<TRect>& aRect)
    {
    TRect rect(aRect().iTl, TSize(aWidth, aRect().Height()));
    aRect = rect;
    }

EXPORT_C void PropertyAdapters::FromHeightToRect(const PropertyBase<TInt>& aHeight, PropertyBase<TRect>& aRect)
    {
    TRect rect(aRect().iTl, TSize(aRect().Width(), aHeight));
    aRect = rect;
    }

EXPORT_C void PropertyAdapters::FromBottomRightToRect(const PropertyBase<TPoint>& aBottomRight, PropertyBase<TRect>& aRect)
    {
    TRect rect(aBottomRight() - aRect().Size(), aBottomRight);
    aRect = rect;
    }

EXPORT_C void PropertyAdapters::FromHAlignmentToAlignment(const PropertyBase<HAlignment::Align>& aHAlign,
        PropertyBase<Alignment::Align>& aAlignment)
    {
    aAlignment = (Alignment::Align)(aAlignment() & (0x0F | aHAlign()));
    }

EXPORT_C void PropertyAdapters::FromVAlignmentToAlignment(const PropertyBase<VAlignment::Align>& aVAlign,
        PropertyBase<Alignment::Align>& aAlignment)
    {
    aAlignment = (Alignment::Align)(aAlignment() & (0xF0 | aVAlign()));
    }
