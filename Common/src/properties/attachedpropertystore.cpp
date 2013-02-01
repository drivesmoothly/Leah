// USER INCLUDES
#include "attachedpropertystore.h"
#include "property.h"

// ----------------------------------------------------------------------------
// AttachedPropertyStore::AttachedPropertyStore
// Constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C AttachedPropertyStore::AttachedPropertyStore()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// AttachedPropertyStore::~AttachedPropertyStore
// Destructor,
// ----------------------------------------------------------------------------
//
EXPORT_C AttachedPropertyStore::~AttachedPropertyStore()
    {
    THashMapIter<TUint, RPropertyBase*> iter(_properties);
    RPropertyBase* const * value = NULL;
    while ((value = iter.NextValue()))
        {
        delete *value;
        }
    _properties.Close();
    }

// ----------------------------------------------------------------------------
// AttachedPropertyStore::AddProperty
// Adds a property to the store.
// ----------------------------------------------------------------------------
//
EXPORT_C void AttachedPropertyStore::AddPropertyImpl(
        const TUint aPropertyId, RPropertyBase* aProperty)
    {
    RPropertyBase** existingProperty = _properties.Find(aPropertyId);
    ASSERT(existingProperty == NULL);
    _properties.Insert(aPropertyId, aProperty);
    }

// ----------------------------------------------------------------------------
// AttachedProperties::Property
// Retrieves a property from the store.
// ----------------------------------------------------------------------------
//
EXPORT_C RPropertyBase* AttachedPropertyStore::GetPropertyImpl(
        const TUint aPropertyId) const
    {
    RPropertyBase* const * existingProperty = _properties.Find(aPropertyId);
    return (existingProperty == NULL ? NULL : *existingProperty);
    }
