ServerConfig.LS = {
    Log = {
		nLogLevelMask = lltAll - lltDebug,
		nLogOutputMask = lotFile,
		bEnableLogThread = true,
		bFlushFile = true,
        bPrintThreadID = true,
    },

    Net = {
		nMaxAcceptor = 4,
		nMaxConnector = 32,
		nMaxSessionCount = 64,
		nSendBufSize = 1024 * 1024 * 16,
		nRecvBufSize = 1024 * 1024 * 16,
		nPacketBufferSize = 1024 * 64,

		nSmallPacketCount = 1024 * 64,
		nLargePacketCount = 128,
    },
    	
    dwPort = 8201,

	--authorize
	bOAAuthorizeEnable = true,
	nInitAuthCount = 1024 * 4,
	nTotalAuthingCount = 1024 * 4,
	szConfigFile = "oa_authorize\\oa_authorize_external.conf",
};
