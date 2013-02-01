// USER INCLUDES
#include "stackpanel.h"
#include "numericutils.h"
#include "defaultpropertystore.h"

/// Attachable properties
Property<HAlignment::Align>* const StackPanel::HAlign = NULL;
Property<VAlignment::Align>* const StackPanel::VAlign = NULL;
/// Static members
HAlignment::Align StackPanel::DefaultHAlign(HAlignment::ELeft);
VAlignment::Align StackPanel::DefaultVAlign(VAlignment::ETop);

// ----------------------------------------------------------------------------
// StackPanel::StackPanel
// Constructor.
// ----------------------------------------------------------------------------
//
StackPanel::StackPanel()
: Orientation(StackPanelOrientation::EVertical)
    {
    // No implementation required.
    }

// ----------------------------------------------------------------------------
// StackPanel::~StackPanel
// Destructor
// ----------------------------------------------------------------------------
//
StackPanel::~StackPanel()
    {
    // No implementation required.
    }

// ----------------------------------------------------------------------------
// StackPanel::SetHAlign
// Sets a value for the HAlign property in the given store.
// ----------------------------------------------------------------------------
//
EXPORT_C void StackPanel::SetHAlign(AttachedPropertyStore& aStore, HAlignment::Align aHAlign)
    {
    aStore.SetValue(&StackPanel::HAlign, aHAlign);
    }

// ----------------------------------------------------------------------------
// StackPanel::SetVAlign
// Sets a value for the VAlign property in the given store.
// ----------------------------------------------------------------------------
//
EXPORT_C void StackPanel::SetVAlign(AttachedPropertyStore& aStore, VAlignment::Align aVAlign)
    {
    aStore.SetValue(&StackPanel::VAlign, aVAlign);
    }

// ----------------------------------------------------------------------------
// StackPanel::GetHAlign
// Retrieves the HAlign property value from the given store.
// ----------------------------------------------------------------------------
//
EXPORT_C Property<HAlignment::Align>& StackPanel::GetHAlign(AttachedPropertyStore& aStore)
    {
    Property<HAlignment::Align>* property = aStore.GetValue(&StackPanel::HAlign);
    if (NULL == property)
        {
        property = DefaultPropertyStore::Instance().GetValue(&StackPanel::HAlign, DefaultHAlign);
        ASSERT(property);
        }
    return *property;
    }

// ----------------------------------------------------------------------------
// StackPanel::GetVAlign
// Retrieves the VAlign property value from the given store.
// ----------------------------------------------------------------------------
//
EXPORT_C Property<VAlignment::Align>& StackPanel::GetVAlign(AttachedPropertyStore& aStore)
    {
    Property<VAlignment::Align>* property = aStore.GetValue(&StackPanel::VAlign);
    if (NULL == property)
        {
        property = DefaultPropertyStore::Instance().GetValue(&StackPanel::VAlign, DefaultVAlign);
        ASSERT(property);
        }
    return *property;
    }

// ----------------------------------------------------------------------------
// StackPanel::Layout
// Performs layout.
// ----------------------------------------------------------------------------
//
EXPORT_C void StackPanel::Layout()
    {
    Measure(Size);
    Arrange(Size);
    }

// ----------------------------------------------------------------------------
// StackPanel::Measure
// Measures the necessary size for the children controls.
// ----------------------------------------------------------------------------
//
EXPORT_C TSize StackPanel::Measure(const TSize& aAvailableSize)
    {
    TSize preferredSize(0, 0);
    TSize availableSize = aAvailableSize;
    if (Orientation == StackPanelOrientation::EVertical)
        {
        availableSize.iHeight = KMaxTInt;
        }
    else
        {
        availableSize.iWidth = KMaxTInt;
        }
    const RControlsArray& childControls = Controls;
    TInt controlsCount = childControls.Count();
    for (TInt i = 0; i < controlsCount; ++i)
        {
        Control& currentControl = *childControls[i];
        TSize controlDesiredSize = currentControl.Measure(availableSize);
        if (Orientation == StackPanelOrientation::EVertical)
            {
            preferredSize.iWidth = Max(preferredSize.iWidth, controlDesiredSize.iWidth);
            preferredSize.iHeight += controlDesiredSize.iHeight;
            }
        else
            {
            preferredSize.iWidth += controlDesiredSize.iWidth;
            preferredSize.iHeight = Max(preferredSize.iHeight, controlDesiredSize.iHeight);
            }
        }
    preferredSize += MarginsSize();
    NumericUtils::LimitSize(preferredSize, aAvailableSize);
    PreferredSize = preferredSize;
    return preferredSize;
    }

// ----------------------------------------------------------------------------
// StackPanel::Arrange
// Arranges the children controls.
// ----------------------------------------------------------------------------
//
EXPORT_C TSize StackPanel::Arrange(const TSize& aFinalSize)
    {
    TPoint controlLocation(0, 0);
    const RControlsArray& childControls = Controls;
    TInt controlsCount = childControls.Count();
    for (TInt i = 0; i < controlsCount; ++i)
        {
        Control& currentControl = *childControls[i];
        TSize preferredSize = currentControl.PreferredSize;
        if (Orientation == StackPanelOrientation::EVertical)
            {
            controlLocation.iX = DoAlign(GetHAlign(currentControl), aFinalSize.iWidth, preferredSize.iWidth);
            currentControl.Location = controlLocation;
            controlLocation.iY += preferredSize.iHeight;
            }
        else
            {
            controlLocation.iY = DoAlign(GetVAlign(currentControl), aFinalSize.iHeight, preferredSize.iHeight);
            currentControl.Location = controlLocation;
            controlLocation.iX += preferredSize.iWidth;
            }
        currentControl.Size = currentControl.PreferredSize;
        }
    return aFinalSize;
    }
