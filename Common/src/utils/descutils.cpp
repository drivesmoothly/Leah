#include "descutils.h"
#include <gdi.h>

// ----------------------------------------------------------------------------
// DescUtils::FindAny
// Finds any character from the list in the source
// ----------------------------------------------------------------------------
//
TInt DescUtils::FindAny(const TDesC& aSource, const TDesC& aList)
    {
    TInt listLength = aList.Length();
    for (TInt i = 0; i < listLength; ++i)
        {
        TInt position = aSource.Locate(aList[i]);
        if (position != KErrNotFound)
            {
            return position;
            }
        }
    return KErrNotFound;
    }

// ----------------------------------------------------------------------------
// DescUtils::FindNewLine
// Finds a new line character in a descriptor.
// ----------------------------------------------------------------------------
//
TInt DescUtils::FindNewLine(const TDesC& aSource)
    {
    return FindAny(aSource, KNewLineCharacters);
    }

// ----------------------------------------------------------------------------
// DescUtils::GetLineLimit
// Finds the text line limit given a text, a font and a width in pixels.
// ----------------------------------------------------------------------------
//
TInt DescUtils::GetLineLimit(
        TInt aLineWidth,
        const TDesC& aText,
        const CFont& aFont)
    {
    TInt textLength = aText.Length();
    TInt currentWidth = 0;
    for (TInt i = 0; i < textLength; ++i)
        {
        currentWidth += aFont.CharWidthInPixels(aText[i]);
        if (currentWidth > aLineWidth)
            {
            return (i - 1);
            }
        }
    return KErrNotFound;
    }
