ServerConfig.BS = {
    Log = {
        nLogLevelMask = lltAll - lltDebug,
        nLogOutputMask = lotFile,
        bEnableLogThread = true,
        bFlushFile = true,
        bPrintThreadID = true;
    },

    Net = {
		nMaxAcceptor = 8,
		nMaxConnector = 32,
		nMaxSessionCount = 64,
		nSendBufSize = 1024 * 1024 * 4,
		nRecvBufSize = 1024 * 1024 * 4,
		nPacketBufferSize = 1024 * 64,

		nSmallPacketCount = 1024 * 64;
		nLargePacketCount = 128;
		
		nMaxOperationPerLoop = 64,
		nSendLoopBufferSize = 64 * 1024,
		nRecvLoopBufferSize = 16 * 1024,
    },

    nMaxClientSessionCount = 8192,
    nWorkThreadCount = 2,
    dwExternalPort = 8701,
    dwInternalPort = 8301,
   
	nGTReportTime = 5000,
	nHoldCliSessionTime = 30000,
};
