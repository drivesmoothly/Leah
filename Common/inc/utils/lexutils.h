#ifndef LEXUTILS_H_
#define LEXUTILS_H_

#include <e32std.h>

/**
 * Provides utility functions for lexxers.
 */
class LexUtils
    {
public:
    /**
     * Retrieves the token between two marks.
     */
    IMPORT_C static TPtrC TokenBetweenMarks(
            const TDesC& aText,
            const TLex& aLexxer,
            const TLexMark& aStartMark,
            const TLexMark& aEndMark);
    /**
     * Skips the mark by a given number of characters.
     */
    IMPORT_C static void SkipMarkBy(
            TLex& aLexxer,
            TLexMark& aMark,
            TInt aCount);
    };

#endif //LEXUTILS_H_
