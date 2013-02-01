#ifndef STREAMUTILS_H_
#define STREAMUTILS_H_

#include <s32strm.h>

class RReadStream;
class RWriteStream;
class Padding;
class Control;

/**
 * Operator to externalize a TInt.
 * @param aStream The stream to write to.
 * @param aInt The TInt to write to stream.
 * @return The stream.
 */
IMPORT_C RWriteStream& operator<<(RWriteStream& aStream, const TInt& aInt);

/**
 * Operator to internalize a TInt.
 * @param aStream The stream to internalize from.
 * @param aInt The TInt to internalize.
 * @return The stream.
 */
IMPORT_C RReadStream& operator>>(RReadStream& aStream, TInt& aInt);

#endif //STREAMUTILS_H_
