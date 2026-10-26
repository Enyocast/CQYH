GLOBAL_CONFIG["MSConfig"] = {
	-- object init count
	nInitSceneCount = 32,
        nInitRoleCount = 64,
        nInitUserCount= 64,
        
	-- log
	nLogLevelMask = lltCritical + lltInfo,
	nLogOutputMask = lotConsole + lotFile,
	bEnableLogThread = false,
        bFlushFile = true,

	-- net
	szAddress = "0.0.0.0",
	dwGTPort = 8904,
	dwGSPort = 8905,
	dwDBPort = 8902,
	dwLSPort = 8903,
	dwBSPort = 8906,
	dwDLPort = 8908,
	dwMonitorForRoleNumberPort = 8991,

	nMaxAcceptor = 8,
	nMaxConnector = 16,
	nMaxSessionCount = 32,
	nSendBufSize = 1024 * 1024 * 4,
	nRecvBufSize = 1024 * 1024 * 4,
	nPacketBufferSize = 1024 * 16,

	nSmallPacketCount = 64 * 1024;
	nLargePacketCount = 1024;

        -- scene
        nInitGSCount = 1;
        nInitGTCount = 1;
	nInitBSCount = 1;
	nInitDLCount = 0;
        
	-- scene clean,unit:s
	nSceneCleanTime = 40;

        -- team
	nInitTeamCount = 128;
	nInitOnlineRoleCount = 128;

	--server_group
	nDBRegisterGroup = 0;
	nInitGroup = GROUP_1 + GROUP_2;
	-- master
	nMasterInitStudentNum = 3;
	nMasterLevelTwoStudentNum = 4,
	nMasterLevelThreeStudentNum = 5,

	nMasterLvlTwoExp = 300,
	nMasterLvlThreeExp = 500,
	}
