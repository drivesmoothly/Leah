#ifndef LEAHSETTINGS_H_
#define LEAHSETTINGS_H_

#include <e32cmn.h>

class RReadStream;
class RWriteStream;

class TLeahSettings
    {
public:
    TLeahSettings();

    inline const TBool& Enabled() const;
    inline void SetEnabled(const TBool& aEnabled);

    inline const TBool& Autostart() const;
    inline void SetAutostart(TBool aAutostart);

    void InternalizeL(RReadStream& aStream);
    void ExternalizeL(RWriteStream& aStream) const;

protected:
    static TBool DefaultSettingEnabled();
    static TBool DefaultSettingAutostart();

protected:
    TBool iEnabled;
    TBool iAutostart;
    };

#include "LeahSettings.inl"

#endif //LEAHSETTINGS_H_
