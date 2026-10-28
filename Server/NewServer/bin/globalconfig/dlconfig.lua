ServerConfig.DL = {
	Log = {
        nLogLevelMask = lltAll,
        nLogOutputMask = lotConsole + lotFile + lotTrace,
        bEnableLogThread = true,
	    bFlushFile = true,
        bPrintThreadID = true,
    },
    
	Net = {
	    nMaxAcceptor = 4,
	    nMaxConnector = 32,
	    nMaxSessionCount = 32,
	    nSendBufSize = 1024 * 1024 * 1,
	    nRecvBufSize = 1024 * 1024 * 1,
	    nPacketBufferSize = 1024 * 1,

	    nSmallPacketCount = 2048;
	    nLargePacketCount = 256,
    },
    
    dwPort = 8801,        

	-- daily collect
	nStartHour = 1,
	nFetchCountPerLoop = 8000,

	nStoneWarID = 21001,
	nStoneMagID = 21002,
	nStoneTaoID = 21003,

	nStoneRankTopCount = 10,

	RenameConfig = {
		NameDB = {
			ip = "127.0.0.1",
			port = 3306,
			account = "root",
			password = "w1378533..",
			db_name = "cqyh_name",
			charset = "utf8",
		},

		RoleDB = 
		{
			-- Guangmang
			[0] =
			{
				ip = "127.0.0.1",
				port = 3306,
				account ="root",
				password = "w1378533..",
				db_name = "win-bti7jtkllvn",
				charset = "utf8",
			},
		},
	},
};

