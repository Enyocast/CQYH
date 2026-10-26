MaintainConfig = {};

MaintainConfig = {        
	-- log
	nLogLevelMask = lltAll,
	nLogOutputMask = lotFile + lotCustom,
	bEnableLogThread = false,
	bFlushFile = true,

	nMaxAcceptor = 4,
	nMaxConnector = 32,
	nMaxSessionCount = 32,
	nSendBufSize = 1024 * 1024 * 1,
	nRecvBufSize = 1024 * 1024 * 1,
	nPacketBufferSize = 1024 * 1,

	nSmallPacketCount = 2048 * 4,
	nLargePacketCount = 128 * 16,
	
	nPingTimeout = 8 * 1000,
	nServerPingInterval = 2 * 1000;
	bPrintThreadID = false,
	nReconnectTime = 4 * 1000,

	szVersionPath = ".\\version",
	szPatchPath = ".\\patch",
	szAreaConfigPath = ".\\area_config",
};
