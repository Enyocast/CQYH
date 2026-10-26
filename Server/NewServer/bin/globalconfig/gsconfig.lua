ServerConfig.GS = {
    Log = {
        nLogLevelMask = lltAll,
	    nLogOutputMask = lotConsole + lotFile + lotTrace,
	    bEnableLogThread = false,
        bFlushFile = true,
        bPrintThreadID = false;
    },
    
	Net = {
	    nMaxAcceptor = 4,                -- IntranetInitParam.nMaxAcceptor
	    nMaxConnector = 32,              -- IntranetInitParam.nMaxConnector
	    nMaxSessionCount = 32,           -- IntranetInitParam.nMaxSessionCount
	    nSendBufSize = 1024 * 1024 * 2,  -- IntranetInitParam.nSendBufSize
	    nRecvBufSize = 1024 * 1024 * 2,  -- IntranetInitParam.nRecvBufSize
	    nPacketBufferSize = 1024 * 8,    -- IntranetInitParam.nPacketBufferSize

	    nSmallPacketCount = 2048,
	    nLargePacketCount = 512,
    },
    
};
