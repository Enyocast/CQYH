GLOBAL_CONFIG["GuardConfig"] = {
	-- log
	nLogLevelMask = lltAll,
	nLogOutputMask = lotFile,
	bEnableLogThread = false,
	bFlushFile = true,

	-- net
	szAddress = "0.0.0.0",
	dwPort = 8810,
	dwRemoteGuardPort = 8811,

	nMaxAcceptor = 4,
	nMaxConnector = 32,
	nMaxSessionCount = 32,
	nSendBufSize = 1024 * 1024 * 1,
	nRecvBufSize = 1024 * 1024 * 1,
	nPacketBufferSize = 1024 * 1,

	nSmallPacketCount = 2048,
	nLargePacketCount = 32,

	nRegisterTimeout = 100 * 1000,
	nPingTimeout = 5 * 1000,

	nLocalGSCount = 2;
	nLocalGTCount = 2;
	nLocalBSCount = 1;
	nLocalLSCount = 1;
	nLocalDLCount = 0;
	nLocalDBCount = 1;
	nLocalMSCount = 1;
	nLocalGMCount = 1,

	szMTUser = "gmjy_yw",
	szMTPwd = "asdQWE!@#",
	szServerVersionPath = ".\\version",
--	RemoteConfig = {
--		[1] = {
--			szAddress = "172.30.66.24",
--			nGSCount = 1;
--			nGTCount = 1;
--		},
--			[2] = {
--				szAddress = "172.30.61.59",
--				nGSCount = 1;
--				nGTCount = 1;
--			},
--    },
}
