#include "streamutils.h"

EXPORT_C RWriteStream& operator<<(RWriteStream& aStream,const TInt& aInt)
    {
    aStream.WriteInt32L(aInt);
    return aStream;
    }

EXPORT_C RReadStream& operator>>(RReadStream& aStream, TInt& aInt)
    {
    aInt = aStream.ReadInt32L();
    return aStream;
    }
