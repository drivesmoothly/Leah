#ifndef NAMEDRESOURCE_H_
#define NAMEDRESOURCE_H_

#include <estring.h>

class RNamedResource
    {
protected:
    IMPORT_C RNamedResource();
public:
    IMPORT_C virtual ~RNamedResource();
    IMPORT_C virtual const TDesC& Name() const;
    IMPORT_C virtual void SetName(const TDesC& aName);

protected:
    LString iName;
    };

#endif //NAMEDRESOURCE_H_
