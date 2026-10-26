GuardConfig = {
	Log = {
	    nLogLevelMask = lltAll,
	    nLogOutputMask = lotFile + lotTrace,
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
	    nPacketBufferSize = 1024 * 1,

	    nSmallPacketCount = 2048,
	    nLargePacketCount = 32 * 4,
    },

	szAddress = "0.0.0.0",
	dwPort = 8810,

	nRegisterGuardTimeout = 100 * 1000,
	nPingGuardTimeout = 300 * 1000,

	nServerPingTimeout = 5000 * 1000,
	nServerPingInterval = 1000,
	nShareMemDisconnectTimeout = 5000 * 1000,
	
	nLocalGSCount = 1,
	nLocalGTCount = 1,
	nLocalBSCount = 1,
	nLocalLSCount = 1,
	nLocalDLCount = 1,
	nLocalDBCount = 1,
	nLocalMSCount = 1,
	nLocalGMCount = 0,
	nLocalMMCount = 0,
	nLocalMGCount = 0,

	szMTUser = "gmjy_yw",
	szMTPwd = "asdQWE!@#",
	szReportAbsolutePath = "c:\\report",
	
	szServerVersionPath = "version", -- obsolete
	szServerPatchPath = "patch", 	 -- obsolete
	szServerRunPath = "..\\",
	--nLogCleanThreshold = 16, -- unit: G Byte
};
