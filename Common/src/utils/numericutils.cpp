#include "numericutils.h"

// ----------------------------------------------------------------------------
// NumericUtils::LimitSize
// Limits a size object to a size limit.
// ----------------------------------------------------------------------------
//
void NumericUtils::LimitSize(TSize& aSize, const TSize& aLimitSize)
    {
    aSize.iWidth = Min(aSize.iWidth, aLimitSize.iWidth);
    aSize.iHeight = Min(aSize.iHeight, aLimitSize.iHeight);
    }

// ----------------------------------------------------------------------------
// NumericUtils::BoundingSize
// Calculates the bounding size for 2 given sizes.
// ----------------------------------------------------------------------------
//
TSize NumericUtils::BoundingSize(const TSize& aSize1, const TSize& aSize2)
    {
    return TSize(Max(aSize1.iWidth, aSize2.iWidth), Max(aSize1.iHeight, aSize2.iHeight));
    }

// ----------------------------------------------------------------------------
// NumericUtils::ScaleSize
// Scales a size by a given factor.
// ----------------------------------------------------------------------------
//
TSize NumericUtils::ScaleSize(const TSize& aSize, const TReal& aFactor)
    {
    return TSize(aSize.iWidth * aFactor, aSize.iHeight * aFactor);
    }

// ----------------------------------------------------------------------------
// NumericUtils::RemoveMargins
// Removes the margins from a size.
// ----------------------------------------------------------------------------
//
TSize NumericUtils::RemoveMargins(const TSize& aSize, const TRect& aMargin)
    {
    return TSize(aSize.iWidth - aMargin.iTl.iX - aMargin.iBr.iX,
            aSize.iHeight - aMargin.iTl.iY - aMargin.iBr.iY);
    }

// ----------------------------------------------------------------------------
// NumericUtils::MarginsSize
// Calculates the margins size.
// ----------------------------------------------------------------------------
//
TSize NumericUtils::MarginsSize(const TRect& aMargin)
    {
    return TSize(aMargin.iTl.iX + aMargin.iBr.iX, aMargin.iTl.iY + aMargin.iBr.iY);
    }
