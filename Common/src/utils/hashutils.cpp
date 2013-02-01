#include "hashutils.h"

// ----------------------------------------------------------------------------
// CustomHash::Integer64
// Calculates hash for a TInt64.
// ----------------------------------------------------------------------------
//
EXPORT_C TUint32 CustomHash::Integer64(const TInt64& aValue)
    {
    return DefaultHash::Integer(I64HIGH(aValue) + I64LOW(aValue));
    }

// ----------------------------------------------------------------------------
// CustomIdentity::Integer64
// Identity for TInt64 variables.
// ----------------------------------------------------------------------------
//
EXPORT_C TBool CustomIdentity::Integer64(const TInt64& aFirst, const TInt64& aSecond)
    {
    return (aFirst == aSecond);
    }
