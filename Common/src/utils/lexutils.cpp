#include "lexutils.h"

EXPORT_C TPtrC LexUtils::TokenBetweenMarks(
        const TDesC& aText,
        const TLex& aLexxer,
        const TLexMark& aStartMark,
        const TLexMark& aEndMark)
    {
    TInt startOffset = aLexxer.MarkedOffset(aStartMark);
    TInt endOffset = aLexxer.MarkedOffset(aEndMark);

    TPtrC token(aText.Ptr() + startOffset, endOffset - startOffset);
    return token;
    }

EXPORT_C void LexUtils::SkipMarkBy(
        TLex& aLexxer,
        TLexMark& aMark,
        TInt aCount)
    {
    TLexMark currentPosMark;
    aLexxer.Mark(currentPosMark);
    aLexxer.UnGetToMark(aMark);
    aLexxer.Inc(aCount);
    aLexxer.Mark(aMark);
    aLexxer.UnGetToMark(currentPosMark);
    }
