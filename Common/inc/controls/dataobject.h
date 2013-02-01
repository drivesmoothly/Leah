#ifndef DATAOBJECT_H_
#define DATAOBJECT_H_

class DataObject
    {
public:
    virtual TAny* GetData(const TDesC& aFormat) = 0;
    };

#endif //DATAOBJECT_H_
