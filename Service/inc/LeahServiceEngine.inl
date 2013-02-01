
const TLeahSettings& CLeahServiceEngine::Settings() const
	{
	return iSettings;
	}

void CLeahServiceEngine::SetSettings(const TLeahSettings& aSettings)
	{
	iSettings = aSettings;
	}

const CLeahServiceServer& CLeahServiceEngine::Server() const
	{
	return iServer;
	}
