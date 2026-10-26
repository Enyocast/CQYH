ServerConfig.MG = {
	Log = {
        nLogLevelMask = lltAll - lltDebug,
        nLogOutputMask = lotFile,
        bEnableLogThread = false,
        bFlushFile = true,
        bPrintThreadID = true;
    },
    
	Net = {
	    nMaxAcceptor = 8,
	    nMaxConnector = 32,
	    nMaxSessionCount = 32,
	    nSendBufSize = 1024 * 1024 * 64,
	    nRecvBufSize = 1024 * 1024 * 64,
	    nPacketBufferSize = 1024 * 64,

	    nSmallPacketCount = 1024 * 1024;
	    nLargePacketCount = 1024 * 64;
	        
		nMaxOperationPerLoop = 64,
		nSendLoopBufferSize = 64 * 1024,
		nRecvLoopBufferSize = 16 * 1024,
    },
    
    nMaxClientSessionCount = 1024 * 10,
    nWorkThreadCount = 2,
    dwStartExternalPort = 8701,
    dwStartInternalPort = 8401,
};
