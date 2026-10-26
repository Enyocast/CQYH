AreaConfig = {};

AreaConfig.MS = {
	szAddress = "127.0.0.1",
		
	-- scene
	nInitGSCount = 1,
	nInitGTCount = 1,
	nInitBSCount = 1,
	nInitDLCount = 1,
	
	--server_group
	nDBRegisterGroup = 1,
	nInitGroup = GROUP_1 + GROUP_2,
};

AreaConfig.Guard = {        
	-- net
	szAddress = "127.0.0.1",
	
	nLocalGSCount = 1,
	nLocalGTCount = 1,
	nLocalBSCount = 1,
	nLocalLSCount = 1,
	nLocalDLCount = 1,
	nLocalDBCount = 1,
	nLocalMSCount = 1,
	
	szMTUser = "lixg1",
	szMTPwd = "lixg1",
	szServerVersionPath = ".\\version",
}