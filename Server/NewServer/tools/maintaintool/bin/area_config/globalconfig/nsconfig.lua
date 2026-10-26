ServerConfig.NS =
{
	Log =
	{
		nLogLevelMask = lltAll,
		nLogOutputMask = lotConsole + lotFile + lotTrace,
		bEnableLogThread = true,
		bFlushFile = true,
		bPrintThreadID = false;
	},

	Net =
	{
		nMaxAcceptor = 32,
		nMaxConnector = 32,
		nMaxSessionCount = 64,
		nSendBufSize = 1024 * 1024 * 16,
		nRecvBufSize = 1024 * 1024 * 16,
		nPacketBufferSize = 1024 * 64,

		nSmallPacketCount = 1024 * 64,
		nLargePacketCount = 1024,

	},

	szAddress = "172.30.66.35",
	dwPort = 8909,

	szDBIPAddress = "172.30.66.24",
	dwDBPort = 3306,
	szDBAccount = "cqyh",
	szDBPassword = "cqyh88888888",
	szDBName = "cqyh_name",
	szDBCharset = "utf8",
	
	nDBPoolSize = 1024,
};
