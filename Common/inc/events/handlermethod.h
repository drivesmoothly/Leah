#ifndef HANDLERMETHOD_H_
#define HANDLERMETHOD_H_

#include <e32std.h>
#include "handlermethodcompare.h"
#include "handlermethodbase.h"

/**
 * Template base class for method handlers with 3 arguments.
 */
template <class T, class V1 = HandlerNoArg, class V2 = HandlerNoArg, class V3 = HandlerNoArg>
class CHandlerMethod : public CHandlerMethodBase, public MHandlerBase<V1, V2, V3>
    {
public:
    typedef T HandlerType;
    typedef void (HandlerType::*HandlerMethod)(V1 aArg1, V2 aArg2, V3 aArg3);

public:
    CHandlerMethod(HandlerType* aObject, HandlerMethod aMethod)
        {
        SetObject(aObject);
        SetFunction(aMethod);
        }

    CHandlerMethod(const CHandlerMethod<T, V1, V2, V3>& aInstance)
        {
        SetObject(aInstance.Object());
        SetFunction(aInstance.Function());
        }

    /**
     * From _MHandlerBase, Accept.
     * @param aVisitor The visitor to accept.
     */
    void Accept(MHandlerVisitor& aVisitor) const
        {
        aVisitor.Visit((CHandlerMethodBase&)*this);
        }

    /**
     * Polymorphic compare operator.
     * @param aInstance The instance to compare with.
     * @return ETrue if the instances are equal, EFalse otherwise.
     */
    TBool Equals(const _MHandlerBase& aInstance)
        {
        THandlerMethodCompare compare(*this);
        aInstance.Accept(compare);
        return compare.Result();
        }

    /**
     * From MEventHandlerBase0, Call.
     */
    void Call(V1 aArg1, V2 aArg2, V3 aArg3)
        {
        if (Object() && Function() != NULL)
            (Object()->*Function())(aArg1, aArg2, aArg3);
        }

    /**
     * Clones the handler.
     * @return A pointer to a new instance.
     */
    MHandlerBase<V1, V2, V3>* CloneL() const
        {
        return new (ELeave) CHandlerMethod<T, V1, V2, V3>(*this);
        }

    /**
     * Getter for object.
     * @return A pointer to the object.
     */
    inline HandlerType* const Object() const
        {
        return reinterpret_cast<HandlerType*>(iObject);
        }

    /**
     * Getter for the function.
     * A pointer to the member function.
     */
    inline HandlerMethod Function() const
        {
        return reinterpret_cast<HandlerMethod>(iFunction);
        }

protected:
    /**
     * Setter for the object.
     */
    inline void SetObject(HandlerType* aObject)
        {
        iObject = aObject;
        }

    /**
     * Setter for the function.
     */
    inline void SetFunction(HandlerMethod aFunction)
        {
        iFunction = reinterpret_cast<CHandlerMethodBase::Function>(aFunction);
        }
    };

/**
 * Template partial specialization base class for method handlers with no argument.
 */
template <class T>
class CHandlerMethod<T, HandlerNoArg, HandlerNoArg, HandlerNoArg> :
    public CHandlerMethodBase,
    public MHandlerBase<>
    {
public:
    typedef T HandlerType;
    typedef void (HandlerType::*HandlerMethod)();

public:

    CHandlerMethod(HandlerType* aObject, HandlerMethod aMethod)
        {
        SetObject(aObject);
        SetFunction(aMethod);
        }

    CHandlerMethod(const CHandlerMethod<T>& aInstance)
        {
        SetObject(aInstance.Object());
        SetFunction(aInstance.Function());
        }

    /**
     * From _MHandlerBase, Accept.
     * @param aVisitor The visitor to accept.
     */
    void Accept(MHandlerVisitor& aVisitor) const
        {
        aVisitor.Visit((CHandlerMethodBase&)*this);
        }

    /**
     * Polymorphic compare operator.
     * @param aInstance The instance to compare with.
     * @return ETrue if the instances are equal, EFalse otherwise.
     */
    TBool Equals(const _MHandlerBase& aInstance)
        {
        THandlerMethodCompare compare(*this);
        aInstance.Accept(compare);
        return compare.Result();
        }

    /**
     * From MHandlerBase<>, Call.
     */
    void Call()
        {
        if (Object() && Function() != NULL)
            (Object()->*Function())();
        }

    /**
     * Clones the handler.
     * @return A pointer to a new instance.
     */
    MHandlerBase<>* CloneL() const
        {
        return new (ELeave) CHandlerMethod<T>(*this);
        }

    /**
     * Getter for object.
     * @return A pointer to the object.
     */
    inline HandlerType* const Object() const
        {
        return reinterpret_cast<HandlerType*>(iObject);
        }

    /**
     * Getter for the function.
     * A pointer to the member function.
     */
    inline HandlerMethod Function() const
        {
        return reinterpret_cast<HandlerMethod>(iFunction);
        }

protected:
    /**
     * Setter for the object.
     */
    inline void SetObject(HandlerType* aObject)
        {
        iObject = aObject;
        }

    /**
     * Setter for the function.
     */
    inline void SetFunction(HandlerMethod aFunction)
        {
        iFunction = reinterpret_cast<CHandlerMethodBase::Function>(aFunction);
        }
    };

/**
 * Template partial specialization base class for method handlers with 1 argument.
 */
template <class T, class V1>
class CHandlerMethod<T, V1, HandlerNoArg, HandlerNoArg> :
    public CHandlerMethodBase,
    public MHandlerBase<V1>
    {
public:
    typedef T HandlerType;
    typedef void (HandlerType::*HandlerMethod)(V1);

public:

    CHandlerMethod(HandlerType* aObject, HandlerMethod aMethod)
        {
        SetObject(aObject);
        SetFunction(aMethod);
        }

    CHandlerMethod(const CHandlerMethod<T>& aInstance)
        {
        SetObject(aInstance.Object());
        SetFunction(aInstance.Function());
        }

    /**
     * From _MHandlerBase, Accept.
     * @param aVisitor The visitor to accept.
     */
    void Accept(MHandlerVisitor& aVisitor) const
        {
        aVisitor.Visit((CHandlerMethodBase&)*this);
        }

    /**
     * Polymorphic compare operator.
     * @param aInstance The instance to compare with.
     * @return ETrue if the instances are equal, EFalse otherwise.
     */
    TBool Equals(const _MHandlerBase& aInstance)
        {
        THandlerMethodCompare compare(*this);
        aInstance.Accept(compare);
        return compare.Result();
        }

    /**
     * From MHandlerBase<>, Call.
     */
    void Call(V1 aArg1)
        {
        if (Object() && Function() != NULL)
            (Object()->*Function())(aArg1);
        }

    /**
     * Clones the handler.
     * @return A pointer to a new instance.
     */
    MHandlerBase<V1>* CloneL() const
        {
        return new (ELeave) CHandlerMethod<T, V1>(*this);
        }

    /**
     * Getter for object.
     * @return A pointer to the object.
     */
    inline HandlerType* const Object() const
        {
        return reinterpret_cast<HandlerType*>(iObject);
        }

    /**
     * Getter for the function.
     * A pointer to the member function.
     */
    inline HandlerMethod Function() const
        {
        return reinterpret_cast<HandlerMethod>(iFunction);
        }

protected:
    /**
     * Setter for the object.
     */
    inline void SetObject(HandlerType* aObject)
        {
        iObject = aObject;
        }

    /**
     * Setter for the function.
     */
    inline void SetFunction(HandlerMethod aFunction)
        {
        iFunction = reinterpret_cast<CHandlerMethodBase::Function>(aFunction);
        }
    };

/**
 * Template partial specialization base class for method handlers with 2 arguments.
 */
template <class T, class V1, class V2>
class CHandlerMethod<T, V1, V2, HandlerNoArg> :
    public CHandlerMethodBase,
    public MHandlerBase<V1, V2>
    {
public:
    typedef T HandlerType;
    typedef void (HandlerType::*HandlerMethod)(V1, V2);

public:

    CHandlerMethod(HandlerType* aObject, HandlerMethod aMethod)
        {
        SetObject(aObject);
        SetFunction(aMethod);
        }

    CHandlerMethod(const CHandlerMethod<T>& aInstance)
        {
        SetObject(aInstance.Object());
        SetFunction(aInstance.Function());
        }

    /**
     * From _MHandlerBase, Accept.
     * @param aVisitor The visitor to accept.
     */
    void Accept(MHandlerVisitor& aVisitor) const
        {
        aVisitor.Visit((CHandlerMethodBase&)*this);
        }

    /**
     * Polymorphic compare operator.
     * @param aInstance The instance to compare with.
     * @return ETrue if the instances are equal, EFalse otherwise.
     */
    TBool Equals(const _MHandlerBase& aInstance)
        {
        THandlerMethodCompare compare(*this);
        aInstance.Accept(compare);
        return compare.Result();
        }

    /**
     * From MHandlerBase<>, Call.
     */
    void Call(V1 aArg1, V2 aArg2)
        {
        if (Object() && Function() != NULL)
            (Object()->*Function())(aArg1, aArg2);
        }

    /**
     * Clones the handler.
     * @return A pointer to a new instance.
     */
    MHandlerBase<V1, V2>* CloneL() const
        {
        return new (ELeave) CHandlerMethod<T, V1, V2>(*this);
        }

    /**
     * Getter for object.
     * @return A pointer to the object.
     */
    inline HandlerType* const Object() const
        {
        return reinterpret_cast<HandlerType*>(iObject);
        }

    /**
     * Getter for the function.
     * A pointer to the member function.
     */
    inline HandlerMethod Function() const
        {
        return reinterpret_cast<HandlerMethod>(iFunction);
        }

protected:
    /**
     * Setter for the object.
     */
    inline void SetObject(HandlerType* aObject)
        {
        iObject = aObject;
        }

    /**
     * Setter for the function.
     */
    inline void SetFunction(HandlerMethod aFunction)
        {
        iFunction = reinterpret_cast<CHandlerMethodBase::Function>(aFunction);
        }
    };

///////////////////////////////////////////////////////////////////////////////////////////////////

// Factory function for method handlers on stack with no arguments
template <class T>
CHandlerMethod<T> MethodHandler(T* aObject, void (T::*aMethod)())
    {
    return CHandlerMethod<T>(aObject, aMethod);
    }

// Factory function for method handlers on stack with 1 argument.
template <class T, class V1>
CHandlerMethod<T, V1> MethodHandler(T* aObject, void (T::*aMethod)(V1))
    {
    return CHandlerMethod<T, V1>(aObject, aMethod);
    }

// Factory function for method handlers on stack with 2 argument.
template <class T, class V1, class V2>
CHandlerMethod<T, V1, V2> MethodHandler(T* aObject, void (T::*aMethod)(V1, V2))
    {
    return CHandlerMethod<T, V1, V2>(aObject, aMethod);
    }

// Factory function for method handlers on stack with 3 arguments.
template <class T, class V1, class V2, class V3>
CHandlerMethod<T, V1, V2, V3> MethodHandler(T* aObject, void (T::*aMethod)(V1, V2, V3))
    {
    return CHandlerMethod<T, V1, V2, V3>(aObject, aMethod);
    }

#endif //HANDLERMETHOD_H_
