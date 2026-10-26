ServerConfig.GS = {
    Log = {
        nLogLevelMask = lltAll,
	    nLogOutputMask = lotConsole + lotFile + lotTrace,
	    bEnableLogThread = false,
        bFlushFile = true,
        bPrintThreadID = false;
    },
    
	Net = {
	    nMaxAcceptor = 4,
	    nMaxConnector = 32,
	    nMaxSessionCount = 32,
	    nSendBufSize = 1024 * 1024 * 2,
	    nRecvBufSize = 1024 * 1024 * 2,
	    nPacketBufferSize = 1024 * 8,

	    nSmallPacketCount = 2048,
	    nLargePacketCount = 512,
    },
    
};
