

// ----------------------------------------------------------------------------
// DefaultPropertyStore::GetValue
// Gets the property.
// ----------------------------------------------------------------------------
//
template <class Property, class Value>
Property* DefaultPropertyStore::GetValue(Property* const * aProperty, Value aValue)
    {
    Property* property = AttachedPropertyStore::GetValue(aProperty);
    if (NULL == property)
        {
        property = AttachedPropertyStore::SetValue(aProperty, aValue);
        }
    return property;
    }
