#ifndef HANDLERMETHODBASE_H_
#define HANDLERMETHODBASE_H_

#include <e32base.h>
#include "handlersbase.h"
#include "handlermethodcompare.h"

class CHandlerMethodBase : public CBase
    {
public:
    typedef void (CHandlerMethodBase::*Function)();

protected:
    inline CHandlerMethodBase();

    inline CHandlerMethodBase(const CHandlerMethodBase& aInstance);

    inline CHandlerMethodBase(TAny* aObject, Function aFunction);

public:
    /**
     * Equal operator
     */
    inline bool operator ==(const CHandlerMethodBase& aInstance) const;

    /**
     * Not equal operator.
     */
    inline bool operator !=(const CHandlerMethodBase& aInstance) const;

    /**
     * Assignment operator.
     * @param aInstance The instance to copy from.
     * @return A reference to this object.
     */
    inline CHandlerMethodBase& operator =(const CHandlerMethodBase& aInstance);

protected:
    TAny* iObject;
    Function iFunction;
    };

#include "handlermethodbase.inl"

#endif //HANDLERMETHODBASE_H_
