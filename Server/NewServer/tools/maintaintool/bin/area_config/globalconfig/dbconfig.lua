ServerConfig.DB = {
    Log = {
        nLogLevelMask = lltAll - lltDebug,
        nLogOutputMask = lotFile,
        bEnableLogThread = true,
        bFlushFile = true,
        bPrintThreadID = false;
    },
    
    Net = {
		nMaxAcceptor = 4,
		nMaxConnector = 32,
		nMaxSessionCount = 64,
		nSendBufSize = 1024 * 1024 * 64,
		nRecvBufSize = 1024 * 1024 * 64,
		nPacketBufferSize = 1024 * 64,

		nSmallPacketCount = 1024 * 256,
		nLargePacketCount = 1024 * 64,
    },

	dwPort = 8501,

	bUseIndependentDB = true,

	-- mysql db	
	szDBIPAddress = "127.0.0.1",
	dwDBPort = 3306,
	szDBAccount = "cqyh",
	szDBPassword = "cqyh88888888",
	szDBName = "cqyh",
	szDBCharset = "utf8",

	-- mysql log db
	szLogDBIPAddress = "172.30.66.24",
	dwLogDBPort = 3306,
	szLogDBAccount = "cqyh",
	szLogDBPassword = "cqyh88888888",
	szLogDBName = "cqyh",
	szLogDBCharset = "utf8",

	-- mysql db , slaver
	szSlaverDBIPAddress = "172.30.66.24",
	dwSlaverDBPort = 3306,
	szSlaverDBAccount = "cqyh",
	szSlaverDBPassword = "cqyh88888888",
	szSlaverDBName = "cqyh",
	szSlaverDBCharset = "utf8",
	
	-- logic
	dwMaxCache = 64000 * 4,
	dwThreadCount = 4,
	dwProcessCount = 100,
	dwDBCloseTimeout = 16000,
};
