#include "propertyholder.h"

EXPORT_C RPropertyHolder::RPropertyHolder()
    {
    // No implementation required
    }

EXPORT_C RPropertyHolder::~RPropertyHolder()
    {
    GetProperties().Close();
    }

EXPORT_C const RPropertyArray& RPropertyHolder::Properties() const
    {
    return iProperties;
    }

EXPORT_C RPropertyArray& RPropertyHolder::GetProperties()
    {
    return iProperties;
    }
