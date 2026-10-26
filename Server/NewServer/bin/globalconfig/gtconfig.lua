ServerConfig.GT = {
	Log = {
        nLogLevelMask = lltAll,
        nLogOutputMask = lotConsole + lotFile,
        bEnableLogThread = false,
        bFlushFile = true,
        bPrintThreadID = true;
    },
    
	Net = {
	    nMaxAcceptor = 8,                  -- internal - IntranetInitParam.nMaxAcceptor
	    nMaxConnector = 32,                -- internal - IntranetInitParam.nMaxConnector
	    nSendBufSize = 1024 * 1024 * 2,    -- internal - IntranetInitParam.nSendBufSize
	    nRecvBufSize = 1024 * 1024 * 2,    -- internal - IntranetInitParam.nRecvBufSize
	    nPacketBufferSize = 1024 * 8,      -- internal - IntranetInitParam.nPacketBufferSize

	    nSmallPacketCount = 2048;
	    nLargePacketCount = 128;

	    nMaxSessionCount = 32,            -- external/internal - IocpInitParam.nMaxSessionCount, IntranetInitParam.nMaxSessionCount
		nMaxOperationPerLoop = 64,        -- external - IocpInitParam.nMaxOperationPerLoop
		nSendLoopBufferSize = 64 * 1024,  -- external - IocpInitParam.nRecvLoopBufferSize
		nRecvLoopBufferSize = 16 * 1024,  -- external - IocpInitParam.nSendLoopBufferSize
    },
    
    nMaxClientSessionCount = 1024,
    nWorkThreadCount = 2,  -- external - IocpInitParam.nThreadCount
    dwStartExternalPort = 8701,
    dwStartInternalPort = 8401,
    
	nLoginAuthTimeout = 30000,
    nRoleOperateTimeout = 600000,
	nPlayingTimeout = 300000,
	nWorldID = 1,
	bLogMessage = true,
	nEncryptCode = 0x81,
};
