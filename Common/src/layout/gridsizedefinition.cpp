#include "gridsizedefinition.h"

// ----------------------------------------------------------------------------
// Grid::SizeDefinition::operator ==
// Checks if two size definitions are equal.
// ----------------------------------------------------------------------------
//
TBool GridSizeDefinition::operator ==(const GridSizeDefinition& aInstance) const
    {
    return (iValue == aInstance.iValue) && (iType == aInstance.iType);
    }

// ----------------------------------------------------------------------------
// Grid::SizeDefinition::operator !=
// Checks if two size definitions are equal.
// ----------------------------------------------------------------------------
//
TBool GridSizeDefinition::operator !=(const GridSizeDefinition& aInstance) const
    {
    return !(*this == aInstance);
    }
