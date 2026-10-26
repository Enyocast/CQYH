ServerConfig.DB = {
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
	    nPacketBufferSize = 1024 * 8,

	    nSmallPacketCount = 512,
	    nLargePacketCount = 128,
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
	szLogDBIPAddress = "127.0.0.1",
	dwLogDBPort = 3306,
	szLogDBAccount = "cqyh",
	szLogDBPassword = "cqyh88888888",
	szLogDBName = "cqyh",
	szLogDBCharset = "utf8",

	-- mysql db , slaver
	szSlaverDBIPAddress = "127.0.0.1",
	dwSlaverDBPort = 3306,
	szSlaverDBAccount = "cqyh",
	szSlaverDBPassword = "cqyh88888888",
	szSlaverDBName = "cqyh_role_99",
	szSlaverDBCharset = "utf8",

	-- mysql log db, slaver
	szSlaverLogDBIPAddress = "127.0.0.1",
	dwSlaverLogDBPort = 3306,
	szSlaverLogDBAccount = "cqyh",
	szSlaverLogDBPassword = "cqyh88888888",
	szSlaverLogDBName = "sh_taoqun_d_log",
	szSlaverLogDBCharset = "utf8",

	-- logic
	dwMaxCache = 1000,
	dwThreadCount = 4,
	dwProcessCount = 100,
	dwDBCloseTimeout = 16000,

};
