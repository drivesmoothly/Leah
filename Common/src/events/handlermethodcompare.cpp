#include "handlermethodcompare.h"
#include "handlermethodbase.h"

EXPORT_C THandlerMethodCompare::THandlerMethodCompare(CHandlerMethodBase& aFirst)
: iFirst(aFirst), iResult(EFalse)
    {

    }

EXPORT_C void THandlerMethodCompare::Visit(const _MHandlerBase& /*aSecond*/)
    {
    SetResult(EFalse);
    }

EXPORT_C void THandlerMethodCompare::Visit(const CHandlerMethodBase& aSecond)
    {
    SetResult(iFirst == aSecond);
    }
