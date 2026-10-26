GLOBAL_CONFIG["DBConfig"] = {
	-- log
	nLogLevelMask = lltCritical + lltInfo,
        nLogOutputMask = lotFile,
        bEnableLogThread = false,
        bFlushFile = true,

	-- mysql db
	bUseIndependentDB = true,	
        szDBIPAddress = "172.30.10.183",
        dwDBPort = 3306,
        szDBAccount = "Jiutian",
        szDBPassword = "JiutianSky",
--        szDBName = "wbtest_myisam",
	szDBName = "jtdb",
	szDBName_LogData = "jtdb_logdata",
    szDBCharset = "utf8",

	-- logic
	dwMaxCache = 30000,
	dwThreadCount = 4,
	dwProcessCount = 100,
	dwDBCloseTimeout = 16000,

	-- net
	nMaxAcceptor = 4,
	nMaxConnector = 16,
	nMaxSessionCount = 32,
	nSendBufSize = 1024 * 1024 * 4,
	nRecvBufSize = 1024 * 1024 * 4,
	nPacketBufferSize = 1024 * 8,

	nSmallPacketCount = 64 * 1024,
	nLargePacketCount = 1024,

	dwPort = 8501,
};
