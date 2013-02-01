#include "propertybase.h"
#include "propertybind.h"

/// ===========================================================================
/// RPropertyBase
/// ===========================================================================

EXPORT_C RPropertyBase::~RPropertyBase()
    {
    }

EXPORT_C void RPropertyBase::AddBindL(PropertyBind& aBind)
    {
    iBinds.AppendL(&aBind);
    }

EXPORT_C void RPropertyBase::RemoveBind(PropertyBind& aBind)
    {
    TInt index = iBinds.Find(&aBind);
    if (KErrNotFound != index)
        {
        iBinds.Remove(index);
        }
    }

EXPORT_C void RPropertyBase::ClearBinds()
    {
    while (iBinds.Count())
        iBinds[0]->UnBind();
    iBinds.Reset();
    }
