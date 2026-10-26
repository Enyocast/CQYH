ServerConfig.MG = {
	Log = {
        nLogLevelMask = lltAll,
        nLogOutputMask = lotConsole + lotFile,
        bEnableLogThread = false,
        bFlushFile = true,
        bPrintThreadID = true;
    },
    
	Net = {
	    nMaxAcceptor = 8,
	    nMaxConnector = 32,
	    nMaxSessionCount = 32,
	    nSendBufSize = 1024 * 1024 * 2,
	    nRecvBufSize = 1024 * 1024 * 2,
	    nPacketBufferSize = 1024 * 8,

	    nSmallPacketCount = 2048;
	    nLargePacketCount = 128;	
	        
		nMaxOperationPerLoop = 64,
		nSendLoopBufferSize = 64 * 1024,
		nRecvLoopBufferSize = 16 * 1024,
    },
    
    nMaxClientSessionCount = 1024,
    nWorkThreadCount = 1,
    dwStartExternalPort = 8701,
    dwStartInternalPort = 8401,
};
