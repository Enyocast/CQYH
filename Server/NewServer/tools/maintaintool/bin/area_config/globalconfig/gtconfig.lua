ServerConfig.GT = {
    Log = {
		nLogLevelMask = lltAll - lltDebug,
		nLogOutputMask = lotFile,
		bEnableLogThread = true,
		bFlushFile = true,
		bPrintThreadID = true;
    },

    Net = {
		nMaxAcceptor = 8,
		nMaxConnector = 64,
		nMaxSessionCount = 64,
		nSendBufSize = 1024 * 1024 * 64,
		nRecvBufSize = 1024 * 1024 * 64,
		nPacketBufferSize = 1024 * 256,

		nSmallPacketCount = 1024 * 1024;
		nLargePacketCount = 1024 * 16;
		  
		nMaxOperationPerLoop = 64,
		nSendLoopBufferSize = 64 * 1024,
		nRecvLoopBufferSize = 16 * 1024,
    },

    nMaxClientSessionCount = 1024 * 10,
    nWorkThreadCount = 2,
	dwStartExternalPort = 8701,
	dwStartInternalPort = 8401,
    
	nLoginAuthTimeout = 600 * 1000,
	nRoleOperateTimeout = 1800 * 1000,
	nPlayingTimeout = 600 * 1000,

	bLogMessage = true,
	nEncryptCode = 0x81,
	dwClientOption = 0,
};
