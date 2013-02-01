const TBool& TLeahSettings::Enabled() const
	{
	return iEnabled;
	}

void TLeahSettings::SetEnabled(const TBool& aEnabled)
	{
	iEnabled = aEnabled;
	}

const TBool& TLeahSettings::Autostart() const
	{
	return iAutostart;
	}

void TLeahSettings::SetAutostart(TBool aAutostart)
	{
	iAutostart = aAutostart;
	}
