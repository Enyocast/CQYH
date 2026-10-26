GLOBAL_CONFIG["ASIMOVConfig"] = {
	nLogLevelMask = lltAll,
        nLogOutputMask = lotFile,
        bEnableLogThread = false,
	bFlushFile = false,

        nSmallPacketCount = 2048,
        nLargePacketCount = 32,

	szAddress = "127.0.0.1",
	dwPort = 8904,

        nMaxSessionCount = 8192,	
	nWorkThreadCount = 4,
        nPacketBufferSize = 1024 * 32,
	nRecvBufSize = 1024 * 1024 * 4,
        nSendBufSize = 1024 * 1024 * 4,
};
