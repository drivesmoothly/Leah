
/// ===========================================================================
/// PropertyReadBase<Type>
/// ===========================================================================

template <class Type>
PropertyReadBase<Type>::operator Type() const
    {
    return Value();
    }

template <class Type>
Type PropertyReadBase<Type>::operator ()() const
    {
    return Value();
    }

/// ===========================================================================
/// PropertyReadBase<Type&>
/// ===========================================================================

template <class Type>
PropertyReadBase<Type&>::operator Type&() const
    {
    return Value();
    }

template <class Type>
Type& PropertyReadBase<Type&>::operator ()() const
    {
    return Value();
    }

template <class Type>
Type* const PropertyReadBase<Type&>::operator ->() const
    {
    return &Value();
    }

/// ===========================================================================
/// PropertyReadBase<Type*>
/// ===========================================================================

template <class Type>
PropertyReadBase<Type*>::operator Type*() const
    {
    return Value();
    }

template <class Type>
Type* PropertyReadBase<Type*>::operator ()() const
    {
    return Value();
    }

template <class Type>
Type* const PropertyReadBase<Type*>::operator ->() const
    {
    return Value();
    }

/// ===========================================================================
/// PropertyBase<Type>
/// ===========================================================================

template <class Type>
PropertyBase<Type>::~PropertyBase()
    {
    RPropertyBase::ClearBinds();
    }

template <class Type>
PropertyBase<Type>& PropertyBase<Type>::operator =(Type aValue)
    {
    SetValue(aValue);
    return *this;
    }

template <class Type>
void PropertyBase<Type>::ReadValue(const TDesC& aText)
    {
    PropertyReader::Read(*this, aText);
    }
