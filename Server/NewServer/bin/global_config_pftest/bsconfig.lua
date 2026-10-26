GLOBAL_CONFIG["BSConfig"] = {
	-- log
	nLogLevelMask = lltAll,
        nLogOutputMask = lotFile,
        bEnableLogThread = false,
        bFlushFile = true,

	-- net
	nMaxAcceptor = 4,
	nMaxConnector = 32,
	nMaxSessionCount = 32,
	nSendBufSize = 1024 * 1024 * 2,
	nRecvBufSize = 1024 * 1024 * 2,
	nPacketBufferSize = 1024 * 1,

	nSmallPacketCount = 2048;
	nLargePacketCount = 32;

        nMaxClientSessionCount = 8192,
        nWorkThreadCount = 2,
        dwExternalPort = 8701,
        dwInternalPort = 8301,
        
        -- 
	nGTReportTime = 5000,
	nHoldCliSessionTime = 30000,
};
