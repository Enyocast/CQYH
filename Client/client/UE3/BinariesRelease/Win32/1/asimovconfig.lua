AsimovConfig = {
    Log = {
        nLogLevelMask = lltInfo + lltCritical + lltWarning + lltError + lltSys + lltLua + lltDebug,
        nLogOutputMask = lotFile + lotTrace,
        bEnableLogThread = true,
        bFlushFile = true,
        bPrintThreadID = true;
    },
    
    Net = {
        nSmallPacketCount = 1024,
        nLargePacketCount = 32,

        nPacketBufferSize = 1024 * 32,
	    nRecvBufSize = 1024 * 1024 * 4,
        nSendBufSize = 1024 * 1024 * 4,
        	        
		nMaxOperationPerLoop = 1024,
		nSendLoopBufferSize = 16 * 1024,
		nRecvLoopBufferSize = 512 * 1024,
    },
    
    szAddress = "127.0.0.1",
    dwPort = 8904,
    nMaxSessionCount = 2048,
    nWorkThreadCount = 4,
};
