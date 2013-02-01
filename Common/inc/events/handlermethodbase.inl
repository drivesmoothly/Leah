#ifndef HANDLERMETHODBASE_INL_
#define HANDLERMETHODBASE_INL_

CHandlerMethodBase::CHandlerMethodBase()
    {
    // No implementation required
    }

CHandlerMethodBase::CHandlerMethodBase(const CHandlerMethodBase& aInstance)
: CBase(), iObject(aInstance.iObject), iFunction(aInstance.iFunction)
    {
    // No implementation required
    }

CHandlerMethodBase::CHandlerMethodBase(TAny* aObject, Function aFunction)
: CBase(), iObject(aObject), iFunction(aFunction)
    {
    // No implementation required
    }

/**
 * Equal operator
 */
bool CHandlerMethodBase::operator ==(const CHandlerMethodBase& aInstance) const
    {
    return (iObject == aInstance.iObject) && (iFunction == aInstance.iFunction);
    }

/**
 * Not equal operator.
 */
bool CHandlerMethodBase::operator !=(const CHandlerMethodBase& aInstance) const
    {
    return !(*this == aInstance);
    }

/**
 * Assignment operator.
 * @param aInstance The instance to copy from.
 * @return A reference to this object.
 */
CHandlerMethodBase& CHandlerMethodBase::operator =(const CHandlerMethodBase& aInstance)
    {
    iObject = aInstance.iObject;
    iFunction = aInstance.iFunction;
    return *this;
    }

#endif /* HANDLERMETHODBASE_INL_ */
