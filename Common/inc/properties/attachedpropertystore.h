#ifndef ATTACHEDPROPERTYSTORE_H_
#define ATTACHEDPROPERTYSTORE_H_

// SYSTEM INCLUDES
#include <e32std.h>
#include <e32hashtab.h>

// FORWARDS
class RPropertyBase;

/**
 * Attached properties store.
 */
class AttachedPropertyStore
    {
public: // Constructors ande destructors
    /**
     * Constructor.
     */
    IMPORT_C AttachedPropertyStore();
    /**
     * Destructor.
     */
    IMPORT_C ~AttachedPropertyStore();

public: // New functions

    /**
     * Sets a value to the given attached property.
     * @remarks A new property is added if not already added.
     * @param aProperty The property to set a value for.
     * @param aValue The value.
     */
    template <class Property, class Value>
    Property* SetValue(Property* const * aProperty, Value aValue);
    /**
     * Retrieves an attached property.
     * @param aProperty The property to retrieve.
     * @return A pointer to the property. Can be NULL.
     */
    template <class Property>
    Property* GetValue(Property* const * aProperty) const;

protected: // New functions
    /**
     * Adds a property to the store.
     * The property is identified by an ID. Typically, this ID is the address of the static
     * attachable property from the owner class.
     * @param aPropertyId The id of property to set a value for.
     * @param aProperty The property to add.
     */
    IMPORT_C void AddPropertyImpl(const TUint aProperyId, RPropertyBase* aProperty);
    /**
     * Retrieves a property from the store.
     * @param aPropertyId The id of the class name for the property.
     * @return A pointer to the requested property. NULL if not found.
     */
    IMPORT_C RPropertyBase* GetPropertyImpl(const TUint aPropertyId) const;

private: // Data
    /// Stores the properties
    RHashMap<TUint, RPropertyBase*> _properties;
    };

// TEMPLATE IMPLEMENTATIONS
#include "attachedpropertystore.inl"

#endif //ATTACHEDPROPERTYSTORE_H_
