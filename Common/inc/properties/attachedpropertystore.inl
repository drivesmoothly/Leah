
// ----------------------------------------------------------------------------
// AttachedPropertyStore::SetValue
// Sets a value to the given property. The property will be added to the store
// if it was not already added.
// ----------------------------------------------------------------------------
//
template <class Property, class Value>
Property* AttachedPropertyStore::SetValue(Property* const * aProperty, Value aValue)
    {
    Property* existingProperty = GetValue(aProperty);
    if (existingProperty)
        {
        *existingProperty = aValue;
        }
    else
        {
        existingProperty = new (ELeave) Property(aValue);
        AddPropertyImpl((TUint)aProperty, existingProperty);
        }
    return existingProperty;
    }

// ----------------------------------------------------------------------------
// AttachedPropertyStore::GetValue
// Retrieves a property from the store.
// ----------------------------------------------------------------------------
//
template <class Property>
Property* AttachedPropertyStore::GetValue(Property* const * aProperty) const
    {
    return static_cast<Property*>(GetPropertyImpl((TUint)aProperty));
    }
