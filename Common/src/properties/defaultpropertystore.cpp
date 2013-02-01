// USER INCLUDES
#include "defaultpropertystore.h"

// Singleton instance
DefaultPropertyStore* DefaultPropertyStore::_instance = NULL;

// ----------------------------------------------------------------------------
// DefaultPropertyStore::Instance
// Retrieves the singleton instance
// ----------------------------------------------------------------------------
//
DefaultPropertyStore& DefaultPropertyStore::Instance()
    {
    if (!_instance)
        {
        _instance = new (ELeave) DefaultPropertyStore();
        }
    return *_instance;
    }

// ----------------------------------------------------------------------------
// DefaultPropertyStore::Close
// Destroys the singleton object.
// ----------------------------------------------------------------------------
//
void DefaultPropertyStore::Close()
    {
    delete _instance;
    _instance = NULL;
    }

// ----------------------------------------------------------------------------
// DefaultPropertyStore::DefaultPropertyStore
// Constructor
// ----------------------------------------------------------------------------
//
DefaultPropertyStore::DefaultPropertyStore()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// DefaultPropertyStore::DefaultPropertyStore
// Copy constructor.
// ----------------------------------------------------------------------------
//
DefaultPropertyStore::DefaultPropertyStore(const DefaultPropertyStore& /*aInstance*/)
    {
    // No implementation required
    }


// ----------------------------------------------------------------------------
// DefaultPropertyStore::~DefaultPropertyStore
// Destructor.
// ----------------------------------------------------------------------------
//
DefaultPropertyStore::~DefaultPropertyStore()
    {
    // No implementation required
    }
