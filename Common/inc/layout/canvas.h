#ifndef CANVAS_H_
#define CANVAS_H_

// USER INCLUDES
#include "panel.h"

// FORWARDS
class AttachedPropertyStore;

/**
 * Canvas layout class responsible for arranging controls in a canvas.
 */
class Canvas : public Panel
    {
public: // Attachable properties
    static Property<TInt>* const Left;
    static Property<TInt>* const Top;

protected: // Default values for attachable properties in case they are not set
    static Property<TInt> DefaultLeft;
    static Property<TInt> DefaultTop;

public: // Constructors and destructor.
    /**
     * Constructor.
     */
    IMPORT_C Canvas();
    /**
     * Destructor.
     */
    IMPORT_C ~Canvas();

public: // New functions
    /**
     * Sets the Left attached property to a store.
     * @param aStore The store to set the property into.
     * @param aLeft The left value.
     */
    IMPORT_C static void SetLeft(AttachedPropertyStore& aStore, TInt aLeft);
    /**
     * Sets the Top attached property to a store.
     * @param aStore The store to set the property into.
     * @param aTop The top value.
     */
    IMPORT_C static void SetTop(AttachedPropertyStore& aStore, TInt aTop);
    /**
     * Retrieves the Left property from a store.
     * @param aStore The store to retrieve the property from.
     * @return A pointer to the property. Can be NULL.
     */
    IMPORT_C static Property<TInt>& GetLeft(AttachedPropertyStore& aStore);
    /**
     * Retrieves the Top property from a store.
     * @param aStore The store to retrieve the property from.
     * @return A pointer to the property. Can be NULL.
     */
    IMPORT_C static Property<TInt>& GetTop(AttachedPropertyStore& aStore);

protected: // From base clases

    /**
     * From Control, Layout.
     */
    IMPORT_C void Layout();
    /**
     * From Control, Measure.
     */
    IMPORT_C TSize Measure(const TSize& aAvailableSize);
    /**
     * From Control, Arrange.
     */
    IMPORT_C TSize Arrange(const TSize& aFinalSize);
    };

#endif //CANVAS_H_
