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

	bUseIndependentDB = false,    -- Set to false for now

	-- mysql db
	szDBIPAddress = "127.0.0.1",
	dwDBPort = 3306,
	szDBAccount = "root",
	szDBPassword = "123456",
	szDBName = "cqyh_name",
	szDBCharset = "utf8",

	-- mysql log db
	szLogDBIPAddress = "127.0.0.1",
	dwLogDBPort = 3306,
	szLogDBAccount = "root",
	szLogDBPassword = "123456",
	szLogDBName = "cqyh_name",
	szLogDBCharset = "utf8",

	-- mysql db , slaver
	szSlaverDBIPAddress = "127.0.0.1",
	dwSlaverDBPort = 3306,
	szSlaverDBAccount = "root",
	szSlaverDBPassword = "123456",
	szSlaverDBName = "cqyh_name",
	szSlaverDBCharset = "utf8",

	-- mysql log db, slaver
	szSlaverLogDBIPAddress = "127.0.0.1",
	dwSlaverLogDBPort = 3306,
	szSlaverLogDBAccount = "root",
	szSlaverLogDBPassword = "123456",
	szSlaverLogDBName = "cqyh_name",
	szSlaverLogDBCharset = "utf8",

	-- logic
	dwMaxCache = 1000,
	dwThreadCount = 4,
	dwProcessCount = 100,
	dwDBCloseTimeout = 16000,

};
