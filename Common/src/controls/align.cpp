#include "align.h"

EXPORT_C HAlignment::Align GetHAlignment(Alignment::Align aAlignment)
    {
    return (HAlignment::Align)(aAlignment & 0xF0);
    }

EXPORT_C VAlignment::Align GetVAlignment(Alignment::Align aAlignment)
    {
    return (VAlignment::Align)(aAlignment & 0xF);
    }

EXPORT_C TInt DoAlign(HAlignment::Align aAlignment, TInt aClientWidth, TInt aActualWidth)
    {
    TInt offset = 0;
    switch (aAlignment)
        {
        case HAlignment::ELeft:
            {
            break;
            }
        case HAlignment::EMid:
            {
            offset = (aClientWidth - aActualWidth) / 2;
            break;
            }
        case HAlignment::ERight:
            {
            offset = (aClientWidth - aActualWidth);
            break;
            }
        case HAlignment::EStretch:
            {
            break;
            }
        default:
            {
            break;
            }
        }
    return offset;
    }

EXPORT_C TInt DoAlign(VAlignment::Align aAlignment, TInt aClientHeight, TInt aActualHeight)
    {
    TInt offset = 0;
    switch (aAlignment)
        {
        case VAlignment::ETop:
            {
            break;
            }
        case VAlignment::EMid:
            {
            offset = (aClientHeight - aActualHeight) / 2;
            break;
            }
        case VAlignment::EBottom:
            {
            offset = (aClientHeight - aActualHeight);
            break;
            }
        case VAlignment::EStretch:
            {
            break;
            }
        default:
            {
            break;
            }
        }
    return offset;
    }

EXPORT_C TPoint DoAlign(Alignment::Align aAlignment, TSize aClientSize, TSize aActualSize)
    {
    TPoint offset;
    offset.iX = DoAlign(GetHAlignment(aAlignment), aClientSize.iWidth, aActualSize.iWidth);
    offset.iY = DoAlign(GetVAlignment(aAlignment), aClientSize.iHeight, aActualSize.iHeight);
    return offset;
    }
