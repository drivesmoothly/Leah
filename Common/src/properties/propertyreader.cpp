#include "propertyreader.h"
#include "propertybase.h"
#include "application.h"
#include "fontsmanager.h"
#include <e32std.h>

using namespace PropertyReader;

// Define the list of integer symbols
const SymbolEntry KIntSymbols[] =
    {
        { EXPANDLIT("true"), ETrue},
        { EXPANDLIT("false"), EFalse},
        { EXPANDLIT("yes"), ETrue},
        { EXPANDLIT("no"), EFalse}
    };
// Store the number of symbols
const TInt KIntSymbolsCount = sizeof(KIntSymbols) / sizeof(SymbolEntry);

// Define the list of Alignment symbols
const SymbolEntry KAlignmentSymbols[] =
    {
        { EXPANDLIT("none"), Alignment::ENone},
        { EXPANDLIT("hleftvtop"), Alignment::EHLeftVTop},
        { EXPANDLIT("lefttop"), Alignment::EHLeftVTop},
        { EXPANDLIT("hleftvmid"), Alignment::EHLeftVMid},
        { EXPANDLIT("leftmid"), Alignment::EHLeftVMid},
        { EXPANDLIT("hleftvbottom"), Alignment::EHLeftVBottom},
        { EXPANDLIT("leftbottom"), Alignment::EHLeftVBottom},
        { EXPANDLIT("hmidvtop"), Alignment::EHMidVTop},
        { EXPANDLIT("midtop"), Alignment::EHMidVTop},
        { EXPANDLIT("hmidvmid"), Alignment::EHMidVMid},
        { EXPANDLIT("midmid"), Alignment::EHMidVMid},
        { EXPANDLIT("mid"), Alignment::EHMidVMid},
        { EXPANDLIT("hmidvbottom"), Alignment::EHMidVBottom},
        { EXPANDLIT("midbottom"), Alignment::EHMidVBottom},
        { EXPANDLIT("hrightvtop"), Alignment::EHRightVTop},
        { EXPANDLIT("righttop"), Alignment::EHRightVTop},
        { EXPANDLIT("hrightvmid"), Alignment::EHRightVMid},
        { EXPANDLIT("rightmid"), Alignment::EHRightVMid},
        { EXPANDLIT("hrightvbottom"), Alignment::EHRightVBottom},
        { EXPANDLIT("rightbottom"), Alignment::EHRightVBottom},
    };
// Store the number of Alignment symbols
const TInt KAlignmentSymbolsCount = sizeof(KAlignmentSymbols) / sizeof(SymbolEntry);

// Define the list of Alignment symbols
const SymbolEntry KHAlignmentSymbols[] =
    {
        { EXPANDLIT("none"), HAlignment::ENone},
        { EXPANDLIT("left"), HAlignment::ELeft},
        { EXPANDLIT("mid"), HAlignment::EMid},
        { EXPANDLIT("center"), HAlignment::EMid},
        { EXPANDLIT("right"), HAlignment::ERight},
        { EXPANDLIT("stretch"), HAlignment::EStretch},
    };
// Store the number of Alignment symbols
const TInt KHAlignmentSymbolsCount = sizeof(KHAlignmentSymbols) / sizeof(SymbolEntry);

// Define the list of Alignment symbols
const SymbolEntry KVAlignmentSymbols[] =
    {
        { EXPANDLIT("none"), VAlignment::ENone},
        { EXPANDLIT("top"), VAlignment::ETop},
        { EXPANDLIT("mid"), VAlignment::EMid},
        { EXPANDLIT("center"), VAlignment::EMid},
        { EXPANDLIT("bottom"), VAlignment::EBottom},
        { EXPANDLIT("stretch"), VAlignment::EStretch},
    };
// Store the number of Alignment symbols
const TInt KVAlignmentSymbolsCount = sizeof(KVAlignmentSymbols) / sizeof(SymbolEntry);

// Define the list of Alignment symbols
const SymbolEntry KColorSymbols[] =
    {
        { EXPANDLIT("black"), KRgbBlack.Value()},
        { EXPANDLIT("darkgrey"), KRgbDarkGray.Value()},
        { EXPANDLIT("darkgray"), KRgbDarkGray.Value()},
        { EXPANDLIT("darkred"), KRgbDarkRed.Value()},
        { EXPANDLIT("darkgreen"), KRgbDarkGreen.Value()},
        { EXPANDLIT("darkyellow"), KRgbDarkYellow.Value()},
        { EXPANDLIT("darkblue"), KRgbDarkBlue.Value()},
        { EXPANDLIT("darkmagenta"), KRgbDarkMagenta.Value()},
        { EXPANDLIT("darkcyan"), KRgbDarkCyan.Value()},
        { EXPANDLIT("red"), KRgbRed.Value()},
        { EXPANDLIT("green"), KRgbGreen.Value()},
        { EXPANDLIT("yellow"), KRgbYellow.Value()},
        { EXPANDLIT("blue"), KRgbBlue.Value()},
        { EXPANDLIT("magenta"), KRgbMagenta.Value()},
        { EXPANDLIT("cyan"), KRgbCyan.Value()},
        { EXPANDLIT("grey"), KRgbGray.Value()},
        { EXPANDLIT("gray"), KRgbGray.Value()},
        { EXPANDLIT("white"), KRgbWhite.Value()},
        { EXPANDLIT("transparent"), KRgbTransparent.Value()},
        { EXPANDLIT("orange"), TRgb(0x00a5ff).Value()},
    };
// Store the number of Alignment symbols
const TInt KColorSymbolsCount = sizeof(KColorSymbols) / sizeof(SymbolEntry);

// Define the list of Alignment symbols
const PropertyReader::SymbolEntry KStackPanelOrientationSymbols[] =
    {
        { EXPANDLIT("horizontal"), StackPanelOrientation::EHorizontal},
        { EXPANDLIT("vertical"), StackPanelOrientation::EVertical},
    };
// Store the number of Alignment symbols
const TInt KStackPanelOrientationSymbolsCount = sizeof(KStackPanelOrientationSymbols) /
        sizeof(PropertyReader::SymbolEntry);

// ----------------------------------------------------------------------------
// PropertyReader::Read(TInt)
// Reads a TInt property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<TInt>& aProperty, const TDesC& aText)
    {
    // An integer value might also be a symbol
    TLex lexxer(aText);
    TInt value;
    if (KErrNone == lexxer.Val(value))
        {
        // Check for values first
        aProperty = value;
        }
    else
        {
        // It might be a symbol
        aProperty = GetSymbolValue(aText, KIntSymbols, KIntSymbolsCount);
        }
    }

// ----------------------------------------------------------------------------
// PropertyReader::Read
// Reads a TPoint property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<TPoint>& aProperty, const TDesC& aText)
    {
    // Format: "<x> <y>"
    TPoint pointValue(0, 0);
    TLex lexxer(aText);
    __ASSERT_ALWAYS(0 == lexxer.Val(pointValue.iX), User::Leave(KErrBadDescriptor));
    lexxer.SkipSpace();
    __ASSERT_ALWAYS(0 == lexxer.Val(pointValue.iY), User::Leave(KErrBadDescriptor));
    aProperty = pointValue;
    }

// ----------------------------------------------------------------------------
// PropertyReader::Read
// Reads a TSize property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<TSize>& aProperty, const TDesC& aText)
    {
    // Format: "<width> <height>"
    TSize sizeValue(0, 0);
    TLex lexxer(aText);
    __ASSERT_ALWAYS(0 == lexxer.Val(sizeValue.iWidth), User::Leave(KErrBadDescriptor));
    lexxer.SkipSpace();
    __ASSERT_ALWAYS(0 == lexxer.Val(sizeValue.iHeight), User::Leave(KErrBadDescriptor));
    aProperty = sizeValue;
    }

// ----------------------------------------------------------------------------
// PropertyReader::Read
// Reads a TRect property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<TRect>& aProperty, const TDesC& aText)
    {
    // The format should be "<left><sep><top><sep><right><sep><bottom>"
    TRect rectValue(0, 0, 0, 0);
    TLex lexxer(aText);
    __ASSERT_ALWAYS(0 == lexxer.Val(rectValue.iTl.iX), User::Leave(KErrBadDescriptor));
    lexxer.SkipSpace();
    __ASSERT_ALWAYS(0 == lexxer.Val(rectValue.iTl.iY), User::Leave(KErrBadDescriptor));
    lexxer.SkipSpace();
    __ASSERT_ALWAYS(0 == lexxer.Val(rectValue.iBr.iX), User::Leave(KErrBadDescriptor));
    lexxer.SkipSpace();
    __ASSERT_ALWAYS(0 == lexxer.Val(rectValue.iBr.iY), User::Leave(KErrBadDescriptor));
    aProperty = rectValue;
    }

// ----------------------------------------------------------------------------
// PropertyReader::Read
// Reads a TDesC property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<const TDesC&>& aProperty, const TDesC& aText)
    {
    aProperty = aText;
    }

// ----------------------------------------------------------------------------
// PropertyReader::Read
// Reads a TRgb property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<TRgb>& aProperty, const TDesC& aText)
    {
    // Format: "<red> <green> <blue> <?alpha>"
    __ASSERT_ALWAYS(aText.Length(), User::Leave(KErrBadDescriptor));
    TLex lexxer(aText);
    TRgb rgbValue(0, 0, 0);
    TInt value;
    if (KErrNone == lexxer.Val(value))
        {
        // We have a rgb combination
        lexxer.SkipSpace();
        rgbValue.SetRed(value);
        __ASSERT_ALWAYS(KErrNone == lexxer.Val(value), User::Leave(KErrBadDescriptor));
        lexxer.SkipSpace();
        rgbValue.SetGreen(value);
        __ASSERT_ALWAYS(KErrNone == lexxer.Val(value), User::Leave(KErrBadDescriptor));
        lexxer.SkipSpace();
        rgbValue.SetBlue(value);
        // Check if we have alpha
        if (0 == lexxer.Val(value))
            {
            rgbValue.SetAlpha(value);
            }
        }
    else if (lexxer.Peek() == '#')
        {
        // We have hexadecimal specified color
        lexxer.Get();
        TUint32 hexValue = 0;
        __ASSERT_ALWAYS(KErrNone == lexxer.Val(hexValue, EHex), User::Leave(KErrBadDescriptor));
        rgbValue.SetRed((hexValue & 0xFF0000) >> 16);
        rgbValue.SetGreen((hexValue & 0xFF00) >> 8);
        rgbValue.SetBlue(hexValue & 0xFF);
        }
    else
        {
        // The color is specified by name
        rgbValue = GetSymbolValue(aText, KColorSymbols, KColorSymbolsCount);
        }
    aProperty = rgbValue;
    }


// ----------------------------------------------------------------------------
// PropertyReader::Read
// Reads a Alignment::Align property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<Alignment::Align>& aProperty, const TDesC& aText)
    {
    // Format: "<alignment symbol>"
    aProperty = (Alignment::Align)(GetSymbolValue(aText, KAlignmentSymbols, KAlignmentSymbolsCount));
    }

// ----------------------------------------------------------------------------
// PropertyReader::Read
// Reads a HAlignment::Align property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<HAlignment::Align>& aProperty, const TDesC& aText)
    {
    // Format: "<alignment symbol>"
    aProperty = (HAlignment::Align)(GetSymbolValue(aText, KHAlignmentSymbols, KHAlignmentSymbolsCount));
    }

// ----------------------------------------------------------------------------
// PropertyReader::Read
// Reads a VAlignment::Align property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<VAlignment::Align>& aProperty, const TDesC& aText)
    {
    // Format: "<alignment symbol>"
    aProperty = (VAlignment::Align)(GetSymbolValue(aText, KVAlignmentSymbols, KVAlignmentSymbolsCount));
    }

// ----------------------------------------------------------------------------
// PropertyReader::Read
// Reads a CFont property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<const CFont*>& aProperty, const TDesC& aText)
    {
    // Format: "<font name>"
    if (0 == aText.CompareF(_L("normal")))
        {
        aProperty = Application::Instance()->Fonts->NormalFont();
        }
    else if (0 == aText.CompareF(_L("title")))
        {
        aProperty = Application::Instance()->Fonts->TitleFont();
        }
    else
        {
        User::Leave(KErrBadDescriptor);
        }
    }

// ----------------------------------------------------------------------------
// PropertyReader::Read
// Reads a Grid::BoundsDefinitions array property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<GridBoundsDefinitions&>& aProperty, const TDesC& aText)
    {
    // Format: "<Auto|d*|dd>..." e.g. "2* 60 Auto *"
    aProperty->Reset();
    TLex lexxer(aText);
    TPtrC token = lexxer.NextToken();
    while (token.Length())
        {
        GridSizeDefinition size;
        if (0 == token.CompareF(_L("auto")))
            {
            size.iType = GridSizeDefinition::EAuto;
            size.iValue = 0;
            }
        else if (token[token.Length() - 1] == '*')
            {
            size.iType = GridSizeDefinition::EWeight;
            TLex16 valLexxer(token.Left(token.Length() - 1));
            TReal value = 1;
            valLexxer.Val(value);
            size.iValue = value;
            }
        else
            {
            size.iType = GridSizeDefinition::EPixels;
            TLex16 valLexxer(token);
            TReal value = 0;
            valLexxer.Val(value);
            size.iValue = value;
            }
        aProperty->AppendL(size);
        token.Set(lexxer.NextToken());
        }
    }

// ----------------------------------------------------------------------------
// PropertyReader::Read
// Reads a StackPanel::TOrientation property.
// ----------------------------------------------------------------------------
//
void PropertyReader::Read(PropertyBase<StackPanelOrientation::TOrientation>& aProperty, const TDesC& aText)
    {
    // Format: "<alignment symbol>"
    aProperty = (StackPanelOrientation::TOrientation)GetSymbolValue(aText, KStackPanelOrientationSymbols,
            KStackPanelOrientationSymbolsCount);
    }

// ----------------------------------------------------------------------------
// PropertyReader::GetSymbolValue
// Reads a symbol and retrieves its value from the symbols table.
// ----------------------------------------------------------------------------
//
TInt PropertyReader::GetSymbolValue(const TDesC& aText, const SymbolEntry* aSymbolsTable,
        TInt aSymbolsCount)
    {
    TInt value(0);
    // Find the symbol in the symbols table
    for (TInt i = 0; i < aSymbolsCount; ++i)
        {
        if (0 == aText.CompareF(aSymbolsTable[i].iSymbol))
            {
            value = aSymbolsTable[i].iValue;
            return value;
            }
        }
    User::Leave(KErrBadDescriptor);
    return KErrNotFound;
    }
