#ifndef PROPERTYYADAPTERS_H_
#define PROPERTYYADAPTERS_H_

#include "propertybase.h"
#include "align.h"

class PropertyAdapters
    {
public:
    IMPORT_C static void FromRectToTop(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aTarget);
    IMPORT_C static void FromRectToLeft(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aTarget);
    IMPORT_C static void FromRectToBottom(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aTarget);
    IMPORT_C static void FromRectToRight(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aTarget);
    IMPORT_C static void FromRectToLocation(const PropertyBase<TRect>& aRect, PropertyBase<TPoint>& aTarget);
    IMPORT_C static void FromRectToSize(const PropertyBase<TRect>& aRect, PropertyBase<TSize>& aTarget);
    IMPORT_C static void FromRectToWidth(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aWidth);
    IMPORT_C static void FromRectToHeight(const PropertyBase<TRect>& aRect, PropertyBase<TInt>& aHeight);
    IMPORT_C static void FromRectToBottomRight(const PropertyBase<TRect>& aRect, PropertyBase<TPoint>& aBottomRight);
    IMPORT_C static void FromAlignmentToHAlignment(const PropertyBase<Alignment::Align>& aAlignment, PropertyBase<HAlignment::Align>& aHAlign);
    IMPORT_C static void FromAlignmentToVAlignment(const PropertyBase<Alignment::Align>& aAlignment, PropertyBase<VAlignment::Align>& aVAlign);

    IMPORT_C static void FromTopToRect(const PropertyBase<TInt>& aTop, PropertyBase<TRect>& aRect);
    IMPORT_C static void FromLeftToRect(const PropertyBase<TInt>& aLeft, PropertyBase<TRect>& aRect);
    IMPORT_C static void FromBottomToRect(const PropertyBase<TInt>& aBottom, PropertyBase<TRect>& aRect);
    IMPORT_C static void FromRightToRect(const PropertyBase<TInt>& aRight, PropertyBase<TRect>& aRect);
    IMPORT_C static void FromLocationToRect(const PropertyBase<TPoint>& aLocation, PropertyBase<TRect>& aRect);
    IMPORT_C static void FromSizeToRect(const PropertyBase<TSize>& aSize, PropertyBase<TRect>& aRect);
    IMPORT_C static void FromWidthToRect(const PropertyBase<TInt>& aWidth, PropertyBase<TRect>& aRect);
    IMPORT_C static void FromHeightToRect(const PropertyBase<TInt>& aHeight, PropertyBase<TRect>& aRect);
    IMPORT_C static void FromBottomRightToRect(const PropertyBase<TPoint>& aBottomRight, PropertyBase<TRect>& aRect);
    IMPORT_C static void FromHAlignmentToAlignment(const PropertyBase<HAlignment::Align>& aHAlign, PropertyBase<Alignment::Align>& aAlignment);
    IMPORT_C static void FromVAlignmentToAlignment(const PropertyBase<VAlignment::Align>& aVAlign, PropertyBase<Alignment::Align>& aAlignment);
    };

#endif //PROPERTYYADAPTERS_H_
