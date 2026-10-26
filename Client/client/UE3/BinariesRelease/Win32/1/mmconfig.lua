ServerConfig.MM = {
	Log = {
	    nLogLevelMask = lltAll,
	    nLogOutputMask = lotConsole + lotFile + lotTrace,
	    bEnableLogThread = false,
	    bFlushFile = true,
        bPrintThreadID = false;
    },

    Net = {
	    nMaxAcceptor = 8,
	    nMaxConnector = 32,
	    nMaxSessionCount = 32,
	    nSendBufSize = 1024 * 1024 * 1,
	    nRecvBufSize = 1024 * 1024 * 1,
	    nPacketBufferSize = 1024 * 1,

	    nSmallPacketCount = 2048,
	    nLargePacketCount = 128,
    },

	szAddress = "127.0.0.1",
	dwMGPort = 9101,
	nInitMGCount = 1,
};
