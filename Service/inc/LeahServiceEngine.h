#ifndef LEAHSERVICEENGINE_H_
#define LEAHSERVICEENGINE_H_

#include <e32base.h>
#include "LeahSettings.h"

class CLeahServiceServer;

class CLeahServiceEngine : public CBase
	{
public:
	static CLeahServiceEngine* NewL(CLeahServiceServer& aServer);
	static CLeahServiceEngine* NewLC(CLeahServiceServer& aServer);
	~CLeahServiceEngine();

public:
    inline const TLeahSettings& Settings() const;
    inline void SetSettings(const TLeahSettings& aSettings);

    inline const CLeahServiceServer& Server() const;

protected:
	CLeahServiceEngine(CLeahServiceServer& aServer);
	void ConstructL();

protected:
    void SaveSettingsL();
    void LoadSettingsL();

private:
    CLeahServiceServer& iServer;
    TLeahSettings iSettings;
	};

#include "LeahServiceEngine.inl"

#endif //LEAHSERVICEENGINE_H_
