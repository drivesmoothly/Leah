#ifndef ALIGN_H_
#define ALIGN_H_

// SYSTEM INCLUDES
#include <e32std.h>

/**
 * Alignment class
 */
struct Alignment
    {
    enum Align
        {
        ENone = 0x00,
        EHLeftVTop = 0x11,
        EHLeftVMid = 0x12,
        EHLeftVBottom = 0x13,
        EHMidVTop = 0x21,
        EHMidVMid = 0x22,
        EHMidVBottom = 0x23,
        EHRightVTop = 0x31,
        EHRightVMid = 0x32,
        EHRightVBottom = 0x33
        };
    };

/**
 * Horizontal alignment class
 */
struct HAlignment
    {
    enum Align
        {
        ENone = 0x00,
        ELeft = 0x10,
        EMid = 0x20,
        ERight = 0x30,
        EStretch = 0x40,
        };
    };

/**
 * Vertical alignment class.
 */
struct VAlignment
    {
    enum Align
        {
        ENone = 0x00,
        ETop = 0x01,
        EMid = 0x02,
        EBottom = 0x03,
        EStretch = 0x04,
        };
    };

IMPORT_C HAlignment::Align GetHAlignment(Alignment::Align aAlignment);
IMPORT_C VAlignment::Align GetVAlignment(Alignment::Align aAlignment);

IMPORT_C TInt DoAlign(HAlignment::Align aAlignment, TInt aClientWidth, TInt aActualWidth);
IMPORT_C TInt DoAlign(VAlignment::Align aAlignment, TInt aClientHeight, TInt aActualHeight);
IMPORT_C TPoint DoAlign(Alignment::Align aAlignment, TSize aClientSize, TSize aActualSize);

#endif // ALIGN_H_
