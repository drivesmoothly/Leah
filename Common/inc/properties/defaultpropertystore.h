#ifndef DEFAULTPROPERTYSTORE_H_
#define DEFAULTPROPERTYSTORE_H_

// USER INCLUDES
#include "attachedpropertystore.h"

/**
 * Property store for default values for attached properties.
 */
class DefaultPropertyStore : public AttachedPropertyStore
    {
public:
    /**
     * Retrieves the singleton instance.
     * @return A reference to the singleton instance.
     */
    static DefaultPropertyStore& Instance();
    /**
     * Closes the instance.
     */
    static void Close();

    /**
     * Retrieves a property from the store. Adds a new property if it does not exist.
     * @param aProperty The property to retreieve.
     * @param aValue The default value for the property.
     * @return A pointer to the property.
     */
    template <class Property, class Value>
    Property* GetValue(Property* const * aProperty, Value aValue);

private:
    /**
     * Default constructor.
     */
    DefaultPropertyStore();
    /**
     * Copy constructor.
     * @param aInstance
     */
    DefaultPropertyStore(const DefaultPropertyStore& aInstance);
    /**
     * Destructor.
     */
    ~DefaultPropertyStore();

private:
    /// The singleton instance
    static DefaultPropertyStore* _instance;
    };

// Inline and template implementation
#include "defaultpropertystore.inl"

#endif //DEFAULTPROPERTYSTORE_H_
