#include "LeahSettings.h"

TLeahSettings::TLeahSettings()
	{
	SetAutostart(DefaultSettingAutostart());
	SetEnabled(DefaultSettingEnabled());
	}

void TLeahSettings::InternalizeL(RReadStream& /*aStream*/)
	{
	}

void TLeahSettings::ExternalizeL(RWriteStream& /*aStream*/) const
	{

	}

TBool TLeahSettings::DefaultSettingAutostart()
	{
	return EFalse;
	}

TBool TLeahSettings::DefaultSettingEnabled()
	{
	return ETrue;
	}
