GLOBAL_CONFIG["GSConfig"] = {
	-- log
	nLogLevelMask = lltCritical + lltInfo,
	nLogOutputMask = lotFile,
	bEnableLogThread = false,
        bFlushFile = true,

	-- net
	nMaxAcceptor = 4,
	nMaxConnector = 8,
	nMaxSessionCount = 16,
	nSendBufSize = 1024 * 1024 * 4,
	nRecvBufSize = 1024 * 1024 * 4,
	nPacketBufferSize = 1024 * 32,

	nSmallPacketCount = 64 * 1024,
	nLargePacketCount = 1024;
}
