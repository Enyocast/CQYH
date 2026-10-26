GLOBAL_CONFIG["GTConfig"] = {
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
	nPacketBufferSize = 1024 * 16,

	nSmallPacketCount = 64 * 1024;
	nLargePacketCount = 1024;

        nMaxClientSessionCount = 8192,
        nWorkThreadCount = 2,
        dwStartExternalPort = 8701,
        dwStartInternalPort = 8401,
        
        -- 
	nLoginAuthTimeout = 600000,
        nRoleOperateTimeout = 600000,
	nPlayingTimeout = 600000,
};
