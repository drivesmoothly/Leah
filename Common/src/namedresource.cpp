#include "namedresource.h"

EXPORT_C RNamedResource::RNamedResource()
    {
    // No implementation required
    }

EXPORT_C RNamedResource::~RNamedResource()
    {
    // No implementation required
    }

EXPORT_C const TDesC& RNamedResource::Name() const
    {
    return iName;
    }

EXPORT_C void RNamedResource::SetName(const TDesC& aName)
    {
    iName = aName;
    }
