GLOBAL_CONFIG["LSConfig"] = {
	-- log
	nLogLevelMask = lltCritical + lltInfo,
        nLogOutputMask = lotFile,
        bEnableLogThread = false,
        bFlushFile = true,

	-- net	
	nMaxAcceptor = 4,
	nMaxConnector = 32,
	nMaxSessionCount = 32,
	nSendBufSize = 1024 * 1024 * 4,
	nRecvBufSize = 1024 * 1024 * 4,
	nPacketBufferSize = 1024 * 1,

	nSmallPacketCount = 512 * 4;
	nLargePacketCount = 8 * 4;
		
        dwPort = 8201,
	--authorize
	bOAAuthorizeEnable = 0,
	nAreaID = 1,
	nInitAuthCount = 32,
	nTotalAuthingCount = 128,
	szConfigFile = "oa_authorize\\oa_authorize.conf",
};
