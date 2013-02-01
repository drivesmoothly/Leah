#ifndef FONTSMANAGER_H_
#define FONTSMANAGER_H_

#include <e32base.h>

class CWsScreenDevice;
class CFont;

class FontsManager : public CBase
    {
public: // Constructors and destructor
    IMPORT_C FontsManager(CWsScreenDevice& aScreen);
    IMPORT_C ~FontsManager();

public: // New functions
    IMPORT_C const CFont* TitleFont();
    IMPORT_C const CFont* NormalFont();

protected: // Data
    CWsScreenDevice& iScreen;
    CFont* iTitleFont;
    CFont* iNormalFont;
    RPointerArray<CFont> iFonts;
    };

#endif //FONTSMANAGER_H_
