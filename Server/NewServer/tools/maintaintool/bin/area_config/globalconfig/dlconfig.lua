ServerConfig.DL = {
    Log = {
        nLogLevelMask = lltAll - lltDebug,
        nLogOutputMask = lotFile,
        bEnableLogThread = true,
        bFlushFile = true,
        bPrintThreadID = false,
    },

    Net = {
    	nMaxAcceptor = 4,
    	nMaxConnector = 32,
    	nMaxSessionCount = 64,
    	nSendBufSize = 1024 * 1024 * 64,
    	nRecvBufSize = 1024 * 1024 * 64,
    	nPacketBufferSize = 1024 * 64,

    	nSmallPacketCount = 1024 * 256;
    	nLargePacketCount = 1024 * 64;
    },

    dwPort = 8801,        
};
