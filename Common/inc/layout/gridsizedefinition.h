#ifndef GRIDSIZEDEFINITION_H_
#define GRIDSIZEDEFINITION_H_

#include <e32cmn.h>

/**
 * Stores a size definition.
 * A size definition can be a column width or a row height.
 */
struct GridSizeDefinition
    {
    /**
     * The size type. Can be auto, weight or size in pixels
     * @remarks The size in pixels can be either width or height,
     * depending if it's a row or a column).
     */
    enum Type
        {
        EAuto,  //!< EAuto      Auto width or height.
        EWeight,//!< EWeight    Weight based width or height.
        EPixels //!< EPixels    Width or height in pixels.
        };
    /**
     * Constructor.
     */
    GridSizeDefinition() : iValue(1), iActualValue(0), iType(EWeight) {}
    // New functions
    /**
     * Checks if two SizeDefinition objects are equal.
     * @param aInstance The SizeDefinition to compare to.
     * @return ETrue if equal, EFalse if not.
     */
    TBool operator ==(const GridSizeDefinition& aInstance) const;
    /**
     * Checks if two SizeDefinition objects are NOT equal.
     * @param aInstance The SizeDefinition object to compare to.
     * @return EFalse if equal, ETrue if not.
     */
    TBool operator !=(const GridSizeDefinition& aInstance) const;

    /// The value used to specify the desired size.
    /// Can be weight factor or fixed size in pixels.
    TReal iValue;
    /// The actual size allocated for the size.
    TInt iActualValue;
    /// The type of size specification.
    Type iType;
    };

typedef RArray<GridSizeDefinition> GridBoundsDefinitions;

#endif //GRIDSIZEDEFINITION_H_
