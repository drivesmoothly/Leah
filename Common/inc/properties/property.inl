#ifndef PROPERTY_INL_
#define PROPERTY_INL_

#include "streamutils.h"

/// ===========================================================================
/// Property<T>
/// ===========================================================================

template <class Type, class StorageType>
Property<Type, StorageType>::Property()
    {
    Mem::FillZ(&iValue, sizeof(StorageType));
    }

template <class Type, class StorageType>
Property<Type, StorageType>::Property(Type aValue)
: iValue(aValue)
    {
    // No implementation required
    }

template <class Type, class StorageType>
Property<Type, StorageType>::Property(const TDesC& aText)
    {
    PropertyBase<Type>::ReadValue(aText);
    }

template <class Type, class StorageType>
Property<Type, StorageType>::~Property()
    {
    }

template <class Type, class StorageType>
Property<Type, StorageType>& Property<Type, StorageType>::operator =(
        const Property<Type, StorageType>& aProperty)
    {
    this->SetValue(aProperty.Value());
    return *this;
    }

template <class Type, class StorageType>
Property<Type, StorageType>& Property<Type, StorageType>::operator =(
        Type aValue)
    {
    this->SetValue(aValue);
    return *this;
    }

template <class Type, class StorageType>
Property<Type, StorageType>& Property<Type, StorageType>::operator =(
        const TDesC& aText)
    {
    this->ReadValue(aText);
    return *this;
    }

template <class Type, class StorageType>
TBool Property<Type, StorageType>::operator ==(Type aValue) const
    {
    return iValue == aValue;
    }

template <class Type, class StorageType>
Type Property<Type, StorageType>::Value() const
    {
    return iValue;
    }

template <class Type, class StorageType>
void Property<Type, StorageType>::SetValue(Type aValue)
    {
    if (iValue != aValue)
        {
        iValue = aValue;
        ValueChanged(*this);
        }
    }

/// ===========================================================================
/// PropertyRead<Type, StorageType>
/// ===========================================================================

template <class Type, class StorageType>
PropertyRead<Type, StorageType>::PropertyRead(Type aValue)
: iValue(aValue)
    {
    // No implementation required
    }

template <class Type, class StorageType>
PropertyRead<Type, StorageType>::~PropertyRead()
    {
    // No implementation required
    }

template <class Type, class StorageType>
Type PropertyRead<Type, StorageType>::Value() const
    {
    return iValue;
    }

/// ===========================================================================
/// PropertyExt<T>
/// ===========================================================================

template <class Type, class Holder>
PropertyExt<Type, Holder>::PropertyExt(Holder& aHolder, Getter aGetter, Setter aSetter)
: iHolder(aHolder), iGetter(aGetter), iSetter(aSetter)
    {
    // No implementation required
    }

template <class Type, class Holder>
PropertyExt<Type, Holder>::~PropertyExt()
    {
    // No implementation required
    }

template <class Type, class Holder>
PropertyExt<Type, Holder>& PropertyExt<Type, Holder>::operator =(
        const PropertyExt<Type, Holder>& aProperty)
    {
    SetValue(aProperty.Value());
    return *this;
    }

template <class Type, class Holder>
PropertyExt<Type, Holder>& PropertyExt<Type, Holder>::operator =(
        Type aValue)
    {
    SetValue(aValue);
    return *this;
    }

template <class Type, class Holder>
Type PropertyExt<Type, Holder>::Value() const
    {
    return (iHolder.*iGetter)();
    }

template <class Type, class Holder>
void PropertyExt<Type, Holder>::SetValue(Type aValue)
    {
    if (Value() != aValue)
        {
        (iHolder.*iSetter)(aValue);
        ValueChanged(*this);
        }
    }

/// ===========================================================================
/// PropertyReadExt<T>
/// ===========================================================================

template <class Type, class Holder>
PropertyReadExt<Type, Holder>::PropertyReadExt(Holder& aHolder, Getter aGetter)
    : iHolder(aHolder), iGetter(aGetter)
    {
    // No implementation required
    }

template <class Type, class Holder>
PropertyReadExt<Type, Holder>::~PropertyReadExt()
    {
    // No implementation required
    }

template <class Type, class Holder>
Type PropertyReadExt<Type, Holder>::Value() const
    {
    return (iHolder.*iGetter)();
    }

/// ===========================================================================
/// PropertyDepend<Type>
/// ===========================================================================

// ----------------------------------------------------------------------------
// PropertyDepend::PropertyDepend
// Constructor.
// ----------------------------------------------------------------------------
//
template <class Type>
template <class DependencyProperty>
PropertyDepend<Type>::PropertyDepend(
        AttachedPropertyStore& aStore, DependencyProperty* const * aDependencyProperty)
: iStore(aStore)
, iValueProperty(NULL)
    {
    iValueProperty = aStore.GetValue(aDependencyProperty);
    if (iValueProperty == NULL)
        {
        Type value;
        aStore.SetValue(aDependencyProperty, value);
        iValueProperty = aStore.GetValue(aDependencyProperty);
        ASSERT(iValueProperty);
        }
    iValueProperty->ValueChanged += MethodHandler(this, &PropertyDepend<Type>::DependencyProperty_Changed);
    }

// ----------------------------------------------------------------------------
// PropertyDepend::PropertyDepend
// Constructor.
// ----------------------------------------------------------------------------
//
template <class Type>
template <class DependencyProperty>
PropertyDepend<Type>::PropertyDepend(
        AttachedPropertyStore& aStore, DependencyProperty* const * aDependencyProperty, Type aValue)
: iStore(aStore)
, iValueProperty(NULL)
    {
    iValueProperty = aStore.GetValue(aDependencyProperty);
    if (iValueProperty == NULL)
        {
        aStore.SetValue(aDependencyProperty, aValue);
        iValueProperty = aStore.GetValue(aDependencyProperty);
        ASSERT(iValueProperty);
        }
    iValueProperty->ValueChanged += MethodHandler(this,
            &PropertyDepend<Type>::DependencyProperty_Changed);
    }

// ----------------------------------------------------------------------------
// PropertyDepend::~PropertyDepend
// Destructor.
// ----------------------------------------------------------------------------
//
template <class Type>
PropertyDepend<Type>::~PropertyDepend()
    {
    iValueProperty->ValueChanged -= MethodHandler(this,
            &PropertyDepend<Type>::DependencyProperty_Changed);
    }

// ----------------------------------------------------------------------------
// PropertyDepend::operator =
// Assignment operator from another PropertyDepend
// ----------------------------------------------------------------------------
//
template <class Type>
PropertyDepend<Type>& PropertyDepend<Type>::operator =( const PropertyDepend<Type>& aProperty)
    {
    SetValue(aProperty.Value());
    return *this;
    }

// ----------------------------------------------------------------------------
// PropertyDepend::operator =
// Assignment operator for a value.
// ----------------------------------------------------------------------------
//
template <class Type>
PropertyDepend<Type>& PropertyDepend<Type>::operator =(Type aValue)
    {
    SetValue(aValue);
    return *this;
    }

// ----------------------------------------------------------------------------
// PropertyDepend::Value
// Retrieves the value.
// ----------------------------------------------------------------------------
//
template <class Type>
Type PropertyDepend<Type>::Value() const
    {
    ASSERT(iValueProperty);
    return iValueProperty->Value();
    }

// ----------------------------------------------------------------------------
// PropertyDepend::SetValue
// Sets a new value to the property.
// ----------------------------------------------------------------------------
//
template <class Type>
void PropertyDepend<Type>::SetValue(Type aValue)
    {
    ASSERT(iValueProperty);
    iValueProperty->SetValue(aValue);
    }

// ----------------------------------------------------------------------------
// PropertyDepend::DependencyProperty_Changed
// Handles DependencyProperty change.
// ----------------------------------------------------------------------------
//
template <class Type>
void PropertyDepend<Type>::DependencyProperty_Changed(const PropertyBase<Type>& /*aProperty*/)
    {
    PropertyBase<Type>::ValueChanged(*this);
    }

#endif //PROPERTY_INL_
