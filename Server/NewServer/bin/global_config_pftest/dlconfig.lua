GLOBAL_CONFIG["DLConfig"] = {
-- log
	nLogLevelMask = lltCritical + lltInfo,
        nLogOutputMask = lotFile,
        bEnableLogThread = false,
        bFlushFile = true,

	-- net
	nMaxAcceptor = 4,
	nMaxConnector = 32,
	nMaxSessionCount = 32,
	nSendBufSize = 1024 * 1024 * 4,
	nRecvBufSize = 1024 * 1024 * 4,
	nPacketBufferSize = 1024 * 1,

	nSmallPacketCount = 2048;
	nLargePacketCount = 32;
        dwPort = 8801,        
};
