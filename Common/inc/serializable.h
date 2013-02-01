#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

class RWriteStream;
class RReadStream;

class MSerializable
    {
public:
    virtual ~MSerializable() {}
    virtual void ExternalizeL(RWriteStream& aStream) const = 0;
    virtual void InternalizeL(RReadStream& aStream) = 0;
    };

#endif //SERIALIZABLE_H_
