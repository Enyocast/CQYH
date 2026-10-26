ServerConfig.GM  = {
	--szConfigPath = "commonconfig",
	-- log
	nLogLevelMask = lltAll,
	nLogOutputMask = lotConsole + lotFile + lotTrace,
	bEnableLogThread = false,
	bFlushFile = true,

	nMaxAcceptor = 4,
	nMaxConnector = 32,
	nMaxSessionCount = 32,
	nSendBufSize = 1024 * 1024 * 2,
	nRecvBufSize = 1024 * 1024 * 2,
	nPacketBufferSize = 1024 * 32,

	nSmallPacketCount = 1024*32,
	nLargePacketCount = 1024*2,

	--
	nRolePoolNum = 128,


	-- net
	szAddress = "0.0.0.0",
	dwMSPort = 9010,
	dwTLPort = 9011,


}

