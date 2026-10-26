ServerConfig.GS = {
    Log = {
		nLogLevelMask = lltAll - lltDebug,
		nLogOutputMask = lotFile,
		bEnableLogThread = true,
		bFlushFile = true,
		bPrintThreadID = true,
    },

    Net = {
		nMaxAcceptor = 4,
		nMaxConnector = 64,
		nMaxSessionCount = 64,
		nSendBufSize = 1024 * 1024 * 64,
		nRecvBufSize = 1024 * 1024 * 64,
		nPacketBufferSize = 1024 * 256,

		nSmallPacketCount = 1024 * 1024,
		nLargePacketCount = 1024 * 16,
    },

};
