#ifndef TEXTSERIALIZABLE_H_
#define TEXTSERIALIZABLE_H_

#include <estring.h>

class MTextSerializable
    {
public:
    virtual ~MTextSerializable() {}
    virtual void ExternalizeTextL(LString& Text) const = 0;
    virtual void InternalizeTextL(const TDesC& aText) = 0;
    };

#endif //TEXTSERIALIZABLE_H_
