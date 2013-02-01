#ifndef DESCUTILS_H_
#define DESCUTILS_H_

#include <e32cmn.h>

_LIT(KNewLineCharacters, "\n");

// FORWARDS
class CFont;

/**
 * Provides utility functions for descriptors.
 */
namespace DescUtils
    {
    /**
     * Finds in source any character from the list.
     * @param aSource The source to find into.
     * @param aList The list of characers to find.
     * @return The index of the first match, or KErrNotFound if no match was found.
     */
    TInt FindAny(const TDesC& aSource, const TDesC& aList);
    /**
     * Finds a new line character.
     * @remarks New line may be more than one character, not only \n.
     * @param aSource The descriptor to find into.
     * @return The index of the first match, or KErrNotFound if no match was found.
     */
    TInt FindNewLine(const TDesC& aSource);
    /**
     * Finds the position of the first character that does not fit into one line of text.
     * @param aLineWidth The line width in pixels.
     * @param aText The text to search.
     * @param aFont The font to use for measuring.
     * @return The index of the first character that does not fit, KErrNotFound on any error.
     */
    TInt GetLineLimit(TInt aLineWidth, const TDesC& aText, const CFont& aFont);
    }

#endif //DESCUTILS_H_
