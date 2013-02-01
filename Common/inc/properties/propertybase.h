#ifndef PROPERTYBASE_H_
#define PROPERTYBASE_H_

#include "namedresource.h"
#include "events.h"
#include "propertyreader.h"

class PropertyBind;

/**
 * Abstract base class for all properties.
 */
class RPropertyBase : public RNamedResource
    {
    friend class PropertyBind;
public: // Constructors and destructor
    IMPORT_C virtual ~RPropertyBase();

protected: // Binding manipulation
    IMPORT_C void AddBindL(PropertyBind& aBind);
    IMPORT_C void RemoveBind(PropertyBind& aBind);
    IMPORT_C void ClearBinds();

private: // Data
    RPointerArray<PropertyBind> iBinds;
    };

/**
 * Template abstract base class for read only properties.
 */
template <class Type>
class PropertyReadBase : public RPropertyBase
    {
public: // Types
    typedef PropertyReadBase<Type> ReadBaseType;

public: // Operators
    virtual operator Type() const;
    virtual Type operator()() const;

public: // New functions
    virtual Type Value() const = 0;
    };

/**
 * Template partial specializastion for reference typed properties.
 */
template <class Type>
class PropertyReadBase<Type&> : public RPropertyBase
    {
public: // Types
    typedef PropertyReadBase<Type> ReadBaseType;

public: // Operators
    virtual operator Type&() const;
    virtual Type& operator()() const;
    virtual Type* const operator ->() const;

public: // New functions
    virtual Type& Value() const = 0;
    };

/**
 * Template partial specialization for pointer typed properties
 */
template <class Type>
class PropertyReadBase<Type*> : public RPropertyBase
    {
public: // Types
    typedef PropertyReadBase<Type> ReadBaseType;

public: // Operators
    virtual operator Type*() const;
    virtual Type* operator()() const;
    virtual Type* const operator ->() const;

public: // New functions
    virtual Type* Value() const = 0;
    };

/**
 * Template abstract base class for properties.
 * Getters return by reference.
 */
template <class Type>
class PropertyBase : public PropertyReadBase<Type>
    {
public: // Types
    typedef PropertyBase<Type> BaseType;

public: // Events
    Event<const PropertyBase<Type>& > ValueChanged;

public: // Constructors and destructors
    ~PropertyBase();

public: // Operators
    PropertyBase<Type>& operator =(Type aValue);

public: // New functions
    virtual void SetValue(Type aValue) = 0;
    virtual void ReadValue(const TDesC& aText);
    };

#include "propertybase.inl"

#endif //PROPERTYBASE_H_
