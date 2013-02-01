#include "fontsmanager.h"
#include <w32std.h>
#include <gdi.h>

EXPORT_C FontsManager::FontsManager(CWsScreenDevice& aScreen)
: iScreen(aScreen)
    {
    // No implementation required
    }

EXPORT_C FontsManager::~FontsManager()
    {
    for (TInt i = 0; i < iFonts.Count(); ++i)
        {
        iScreen.ReleaseFont(iFonts[i]);
        }
    iFonts.Reset();
    }

EXPORT_C const CFont* FontsManager::TitleFont()
    {
    if (NULL == iTitleFont)
        {
        TTypefaceSupport tfs;
        iScreen.TypefaceSupport(tfs, 12);

        TFontSpec spec(tfs.iTypeface.iName, 32);
        spec.iFontStyle.SetBitmapType(EAntiAliasedGlyphBitmap);
        iScreen.GetNearestFontInPixels(iTitleFont, spec);
        iFonts.AppendL(iTitleFont);
        }

    return iTitleFont;
    }

EXPORT_C const CFont* FontsManager::NormalFont()
    {
    if (NULL == iNormalFont)
        {
        TTypefaceSupport tfs;
        iScreen.TypefaceSupport(tfs, 12);

        TFontSpec spec(tfs.iTypeface.iName, 22);
        spec.iFontStyle.SetBitmapType(EAntiAliasedGlyphBitmap);
        iScreen.GetNearestFontInPixels(iNormalFont, spec);
        iFonts.AppendL(iNormalFont);
        }

    return iNormalFont;
    }

