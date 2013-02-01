#include "stringutils.h"

EXPORT_C LString operator +(const TDesC& aText, const TUint16 aChar)
    {
    LString text = aText;
    text += aChar;
    return text;
    }
