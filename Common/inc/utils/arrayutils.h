#ifndef ARRAYUTILS_H_
#define ARRAYUTILS_H_

// SYSTEM INCLUDES
#include <e32cmn.h>

/**
 * Compares two arrays.
 * @param aFirst The first array.
 * @param aSecond The second array.
 * @return ETrue if the arrays are the same, EFalse otherwise.
 */
template <class T>
TBool operator ==(const RArray<T>& aFirst, const RArray<T>& aSecond)
    {
    if (aFirst.Count() != aSecond.Count())
        {
        return EFalse;
        }
    for (TInt i = 0; i < aFirst.Count(); ++i)
        {
        if (aFirst[i] != aSecond[i])
            {
            return EFalse;
            }
        }
    return ETrue;
    }

/**
 * Checks if two arrays are different.
 * @param aFirst The first array.
 * @param aSecond The second array.
 * @return ETrue if the arrays are different, EFalse otherwise.
 */
template <class T>
TBool operator !=(const RArray<T>& aFirst, const RArray<T>& aSecond)
    {
    return !(aFirst == aSecond);
    }

#endif //ARRAYUTILS_H_
