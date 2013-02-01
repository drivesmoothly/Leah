// ----------------------------------------------------------------------------
// NumericUtils::SnapToInterval
// Snaps a numeric value to a given interval, based on min and max values.
// ----------------------------------------------------------------------------
//
template <typename T>
T NumericUtils::SnapToInterval(const T& aValue, const T& aMinValue, const T& aMaxValue)
    {
    if (aValue < aMinValue)
        {
        return aMinValue;
        }
    else if (aValue > aMaxValue)
        {
        return aMaxValue;
        }
    return aValue;
    }
