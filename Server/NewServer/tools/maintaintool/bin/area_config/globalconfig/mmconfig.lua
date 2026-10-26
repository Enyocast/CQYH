ServerConfig.MM = {
	Log = {
	    nLogLevelMask = lltAll - lltDebug,
	    nLogOutputMask = lotFile,
	    bEnableLogThread = true,
	    bFlushFile = true,
        bPrintThreadID = false;
    },

    Net = {
	    nMaxAcceptor = 8,
	    nMaxConnector = 32,
	    nMaxSessionCount = 32,
	    nSendBufSize = 1024 * 1024 * 64,
	    nRecvBufSize = 1024 * 1024 * 64,
	    nPacketBufferSize = 1024 * 64,

	    nSmallPacketCount = 1024 * 1024,
	    nLargePacketCount = 1024 * 64,
    },

	szAddress = "127.0.0.1",
	dwMGPort = 9101,
	nInitMGCount = 1,
};
