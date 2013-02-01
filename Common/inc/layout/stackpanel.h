#ifndef STACKPANEL_H_
#define STACKPANEL_H_

// USER INCLUDES
#include "panel.h"
#include "stackpanelorientation.h"

// FORWARDS
class AttachedPropertyStore;

/**
 * Canvas layout class responsible for arranging controls in a canvas.
 */
class StackPanel : public Panel
    {
public: // Attachable properties
    static Property<HAlignment::Align>* const HAlign;
    static Property<VAlignment::Align>* const VAlign;

protected: // Default values for attachable properties in case they are not set
    static HAlignment::Align DefaultHAlign;
    static VAlignment::Align DefaultVAlign;

public: // Properties
    Property<StackPanelOrientation::TOrientation> Orientation;

public: // Constructors and destructors
    /**
     * Constructor.
     */
    IMPORT_C StackPanel();
    /**
     * Destructor.
     */
    IMPORT_C ~StackPanel();

public: // New functions
    /**
     * Sets the HAlign attached property to a store.
     * @param aStore The store to set the property into.
     * @param aHAlign The align value.
     */
    IMPORT_C static void SetHAlign(AttachedPropertyStore& aStore, HAlignment::Align aHAlign);
    /**
     * Sets the VAlign attached property to a store.
     * @param aStore The store to set the property into.
     * @param aVAlign The align value.
     */
    IMPORT_C static void SetVAlign(AttachedPropertyStore& aStore, VAlignment::Align aVAlign);
    /**
     * Retrieves the HAlign property from a store.
     * @param aStore The store to retrieve the property from.
     * @return A pointer to the property. Can be NULL.
     */
    IMPORT_C static Property<HAlignment::Align>& GetHAlign(AttachedPropertyStore& aStore);
    /**
     * Retrieves the VAlign property from a store.
     * @param aStore The store to retrieve the property from.
     * @return A pointer to the property. Can be NULL.
     */
    IMPORT_C static Property<VAlignment::Align>& GetVAlign(AttachedPropertyStore& aStore);

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

#endif //STACKPANEL_H_
