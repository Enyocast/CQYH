ServerConfig.BS = {
    Log = {
        nLogLevelMask = lltAll,
        nLogOutputMask = lotConsole + lotFile + lotTrace,
        bEnableLogThread = false,
        bFlushFile = true,
        bPrintThreadID = true;
    },

    Net = {    
	    nMaxAcceptor = 8,
	    nMaxConnector = 32,
	    nMaxSessionCount = 32,
	    nSendBufSize = 1024 * 1024 * 1,
	    nRecvBufSize = 1024 * 1024 * 1,
	    nPacketBufferSize = 1024 * 1,

	    nSmallPacketCount = 2048;
	    nLargePacketCount = 32;     
	          
		nMaxOperationPerLoop = 64,
		nSendLoopBufferSize = 64 * 1024,
		nRecvLoopBufferSize = 16 * 1024,
    },
    
	nMaxClientSessionCount = 256,
	nWorkThreadCount = 1,
	dwExternalPort = 8701,
	dwInternalPort = 8301,
   
	nGTReportTime = 5000,
	nHoldCliSessionTime = 30000,
	version = 20200516,
	
};
