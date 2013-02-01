// USER INCLUDES
#include "canvas.h"
#include "numericutils.h"

/// Attachable properties
Property<TInt>* const Canvas::Left = NULL;
Property<TInt>* const Canvas::Top = NULL;
/// Static values
Property<TInt> Canvas::DefaultLeft = 0;
Property<TInt> Canvas::DefaultTop = 0;

// ----------------------------------------------------------------------------
// Canvas::Canvas
// Constructor
// ----------------------------------------------------------------------------
//
EXPORT_C Canvas::Canvas()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// Canvas::~Canvas
// Destructor.
// ----------------------------------------------------------------------------
//
EXPORT_C Canvas::~Canvas()
    {
    // No implementation required.
    }

// ----------------------------------------------------------------------------
// Canvas::SetLeft
// Sets the Left attached property to an attached property store.
// ----------------------------------------------------------------------------
//
EXPORT_C void Canvas::SetLeft(AttachedPropertyStore& aStore, TInt aValue)
    {
    aStore.SetValue(&Canvas::Left, aValue);
    }

// ----------------------------------------------------------------------------
// Canvas::GetLeft
// Gets the Left attached property from an attached property store.
// ----------------------------------------------------------------------------
//
EXPORT_C Property<TInt>& Canvas::GetLeft(AttachedPropertyStore& aStore)
    {
    Property<TInt>* property = aStore.GetValue(&Canvas::Left);
    if (NULL == property)
        {
        return DefaultLeft;
        }
    return *property;
    }

// ----------------------------------------------------------------------------
// Canvas::SetTop
// Sets the Top attached property to an attached property store.
// ----------------------------------------------------------------------------
//
EXPORT_C void Canvas::SetTop(AttachedPropertyStore& aStore, TInt aValue)
    {
    aStore.SetValue(&Canvas::Top, aValue);
    }

// ----------------------------------------------------------------------------
// Canvas::GetTop
// Retrieves the Top attached property from an attached property store.
// ----------------------------------------------------------------------------
//
EXPORT_C Property<TInt>& Canvas::GetTop(AttachedPropertyStore& aStore)
    {
    Property<TInt>* property = aStore.GetValue(&Canvas::Top);
    if (NULL == property)
        {
        return DefaultTop;
        }
    return *property;
    }

// ----------------------------------------------------------------------------
// Canvas::Measure
// Calculates the necessary size for the control.
// ----------------------------------------------------------------------------
//
EXPORT_C TSize Canvas::Measure(const TSize& aAvailableSize)
    {
    const RControlsArray& childControls = Controls;
    TInt controlsCount = childControls.Count();
    TSize preferredSize(0, 0);
    for (TInt i = 0; i < controlsCount; ++i)
        {
        Control& currentControl = *childControls[i];
        TSize controlDesiredSize = currentControl.Measure(TSize(KMaxTInt, KMaxTInt));
        TPoint controlPosition(GetLeft(currentControl), GetTop(currentControl));

        preferredSize.iWidth = Max(preferredSize.iWidth, controlDesiredSize.iWidth + controlPosition.iX);
        preferredSize.iHeight = Max(preferredSize.iHeight, controlDesiredSize.iHeight + controlPosition.iY);
        }
    preferredSize += MarginsSize();
    NumericUtils::LimitSize(preferredSize, aAvailableSize);
    PreferredSize = preferredSize;
    return preferredSize;
    }

// ----------------------------------------------------------------------------
// Canvas::Arrange
// Arranges the child controls.
// ----------------------------------------------------------------------------
//
EXPORT_C TSize Canvas::Arrange(const TSize& aFinalSize)
    {
    const RControlsArray& childControls = Controls;
    TInt controlsCount = childControls.Count();
    for (TInt i = 0; i < controlsCount; ++i)
        {
        Control& currentControl = *childControls[i];
        currentControl.Location = TPoint(GetLeft(currentControl), GetTop(currentControl));
        currentControl.Size = currentControl.PreferredSize;
        }
    return aFinalSize;
    }

// ----------------------------------------------------------------------------
// Canvas::Layout
// From Control, Layout.
// ----------------------------------------------------------------------------
//
EXPORT_C void Canvas::Layout()
    {
    Measure(Size);
    Arrange(Size);
    }
