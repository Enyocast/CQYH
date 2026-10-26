ServerConfig.LS = {
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
	    nSendBufSize = 1024 * 1024 * 1,
	    nRecvBufSize = 1024 * 1024 * 1,
	    nPacketBufferSize = 1024 * 1,

	    nSmallPacketCount = 512,
	    nLargePacketCount = 8,
    },
    	
    dwPort = 8201,

	--authorize
	bOAAuthorizeEnable = false,
	nInitAuthCount = 32,
	nTotalAuthingCount = 128,
	szConfigFile = "oa_authorize\\oa_authorize.conf",
};
