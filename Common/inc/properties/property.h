#ifndef PROPERTY_H_
#define PROPERTY_H_

#include <s32strm.h>
#include "propertybase.h"
#include "attachedpropertystore.h"

// FORWARDS
class PropertyBind;

/**
 * Template for typed properties that own the variable.
 */
template <class Type, class StorageType = Type>
class Property : public PropertyBase<Type>
    {
public: // Constructors and destructor
    Property();
    Property(Type aValue);
    Property(const TDesC& aText);
    ~Property();

public: // New operators
    Property<Type, StorageType>& operator =(const Property<Type, StorageType>& aProperty);
    Property<Type, StorageType>& operator =(Type aValue);
    Property<Type, StorageType>& operator =(const TDesC& aText);
    TBool operator ==(Type aValue) const;

public: // From base class
    Type Value() const;
    void SetValue(Type aValue);

protected: // Data
    StorageType iValue;
    };

/**
 * Template specialization for descriptor properties that own the descriptor.
 */
template <>
class Property<const TDesC&, const TDesC&> : public PropertyBase<const TDesC&>
    {
public: // Constructors and destructor
    Property() {}
    Property(const TDesC& aValue) : iValue(aValue) {}

public: // New operators
    Property<const TDesC&, const TDesC&>& operator =(const Property<const TDesC&, const TDesC&>& aProperty)
        {
        SetValue(aProperty.Value());
        return *this;
        }
    Property<const TDesC&, const TDesC&>& operator =(const TDesC& aValue)
        {
        SetValue(aValue);
        return *this;
        }

public: // From base class
    const TDesC& Value() const
        {
        return iValue;
        }
    void SetValue(const TDesC& aValue)
        {
        if (iValue != aValue)
            {
            iValue = aValue;
            ValueChanged(*this);
            }
        }

protected: // Data
    LString iValue;
    };

typedef Property<const TDesC&> PropertyDes;

/**
 * Template for read only typed properties that own the variable.
 */
template <class Type, class StorageType = Type>
class PropertyRead : public PropertyReadBase<Type>
    {
public: // Constructors and destructor
    PropertyRead(Type aValue);
    ~PropertyRead();

public: // From base class
    Type Value() const;

protected: // Data
    StorageType iValue;
    };

/**
 * Template for typed properties that have external getter and setter.
 */
template <class Type, class Holder>
class PropertyExt : public PropertyBase<Type>
    {
    typedef Type (Holder::*Getter)() const;
    typedef void (Holder::*Setter)(Type);

public:
    PropertyExt(Holder& aHolder, Getter aGetter, Setter aSetter);
    ~PropertyExt();

public: // New operators
    PropertyExt<Type, Holder>& operator =(const PropertyExt<Type, Holder>& aProperty);
    PropertyExt<Type, Holder>& operator =(Type aValue);

public: // From base class
    Type Value() const;
    void SetValue(Type aValue);

protected: // Data
    Holder& iHolder;
    Getter iGetter;
    Setter iSetter;
    };

/**
 * Template for read only typed properties that have external getter.
 */
template <class Type, class Holder>
class PropertyReadExt : public PropertyReadBase<Type>
    {
    typedef Type (Holder::*Getter)() const;

public: // Constructors and destructor
    PropertyReadExt(Holder& aHolder, Getter aGetter);
    ~PropertyReadExt();

public: // From base class
    Type Value() const;

protected: // Data
    Holder& iHolder;
    Getter iGetter;
    };

/**
 * Template for typed properties that are an alias of a dependency property.
 */
template <class Type>
class PropertyDepend : public PropertyBase<Type>
    {
public: // Constructors and destructors
    /**
     * Constructor.
     * @param aStore The store for the dependency property.
     * @param aDependencyProperty The dependency property.
     */
    template <class DependencyProperty>
    PropertyDepend(AttachedPropertyStore& aStore, DependencyProperty* const * aDependencyProperty);
    /**
     * Constructor.
     * @param aStore The store for the dependency property.
     * @param aDependencyProperty The dependency property.
     */
    template <class DependencyProperty>
    PropertyDepend(AttachedPropertyStore& aStore, DependencyProperty* const * aDependencyProperty, Type aValue);
    /**
     * Destructor.
     */
    ~PropertyDepend();

public: // New operators
    /**
     * Assignment operator from another PropertyDepend.
     * @param aProperty The other PropertyDepend.
     * @return A reference to this.
     */
    PropertyDepend<Type>& operator =(const PropertyDepend<Type>& aProperty);
    /**
     * Assignment operator from a value.
     * @param aValue The new value.
     * @return A reference to this.
     */
    PropertyDepend<Type>& operator =(Type aValue);

public: // From base class
    /**
     * Retrieves the property value.
     * @return The value.
     */
    Type Value() const;
    /**
     * Sets a new value for the property.
     * @param aValue The new value.
     */
    void SetValue(Type aValue);

protected: // New functions
    /**
     * Handles the dependency property change.
     * @param aDependencyProperty The dependency property.
     */
    void DependencyProperty_Changed(const PropertyBase<Type>& aDependencyProperty);

protected: // Data
    /// The attached properties store.
    AttachedPropertyStore& iStore;
    /// The value property for the dependency property in the store.
    PropertyBase<Type>* iValueProperty;
    };

#include "property.inl"

#endif //PROPERTY_H_
