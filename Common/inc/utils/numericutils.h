#ifndef NUMERICUTILS_H_
#define NUMERICUTILS_H_

#include <e32std.h>

/**
 * Utility functions for numeric types.
 */
namespace NumericUtils
    {
    /**
     * Snaps a value to an interval.
     * If the value is lower than the minimum value, the result is the minimum value.
     * If the value is greater than the maximum value, the result is the maximum value.
     * If the value is between limits, the value is returned.
     * @param aValue The reference value.
     * @param aMinValue The minimum value.
     * @param aMaxValue The maximum value.
     * @return The interval snapping result.
     */
    template <typename T>
    static T SnapToInterval(const T& aValue, const T& aMinValue, const T& aMaxValue);
    /**
     * Limits a size object to a given limit size.
     * @param aSize The size to limit.
     * @param aLimitSize The limit size.
     */
    void LimitSize(TSize& aSize, const TSize& aLimitSize);
    /**
     * Calculates a bounding size for 2 given sizes.
     * The bounding size is the maximum in width and height of the two.
     * @param aSize1 The first size.
     * @param aSize2 The second size.
     * @return The bounding size.
     */
    TSize BoundingSize(const TSize& aSize1, const TSize& aSize2);
    /**
     * Scales a size by a given factor.
     * @param aSize The size to scale.
     * @param aFactor The factor.
     * @return The scaled size.
     */
    TSize ScaleSize(const TSize& aSize, const TReal& aFactor);
    /**
     * Removes the margins from the size.
     * @param aSize The given size, including margins.
     * @param aMargins The margins to remove from the size.
     * @return The size excluding margins.
     */
    TSize RemoveMargins(const TSize& aSize, const TRect& aMargin);
    /**
     * Calculates the margins size from the given margins.
     * @param aMargin The margin.
     * @return The size of the margins.
     */
    TSize MarginsSize(const TRect& aMargin);
    }

#include "numericutils.inl"

#endif //NUMERICUTILS_H_
