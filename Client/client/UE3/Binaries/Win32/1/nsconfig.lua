ServerConfig.NS = 
{
	Log =
	{
		nLogLevelMask = lltAll,
		nLogOutputMask = lotConsole + lotFile + lotTrace,
		bEnableLogThread = false,
		bFlushFile = true,
		bPrintThreadID = false;
	},

	Net = 
	{
		nMaxAcceptor = 32,
		nMaxConnector = 32,
		nMaxSessionCount = 64,
		nSendBufSize = 1024 * 1024 * 1,
		nRecvBufSize = 1024 * 1024 * 1,
		nPacketBufferSize = 1024 * 1,
		
		nSmallPacketCount = 2048,
		nLargePacketCount = 128,
		
	},

	szAddress = "127.0.0.1",
	dwPort = 8997,

	szDBIPAddress = "127.0.0.1",
	dwDBPort = 3306,
	szDBAccount = "cqyh",
	szDBPassword = "cqyh88888888",
	szDBName = "cqyh_name",
	szDBCharset = "utf8",

	nDBPoolSize = 1024,
};
