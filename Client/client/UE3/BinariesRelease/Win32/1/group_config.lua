ServerConfig.GroupConfig = {};

for i = 0, MAX_SERVER_GROUP_COUNT - 1 do
	ServerConfig.GroupConfig[i] = {};
	ServerConfig.GroupConfig[i].nMaxRoleCount = 1;
	ServerConfig.GroupConfig[i].nMaxNewRoleCount = 1;
	ServerConfig.GroupConfig[i].nMaxUserCount = 0;
	ServerConfig.GroupConfig[i].bPrecreateRole = false;
	ServerConfig.GroupConfig[i].szStartDate = "2019-07-02";
	ServerConfig.GroupConfig[i].dwStartDate = 0;

	ServerConfig.GroupConfig[i].nMappedGroupID = 0;
	ServerConfig.GroupConfig[i].bClearGlobalData = false;

	ServerConfig.GroupConfig[i].bUseAllowBits = false;
	ServerConfig.GroupConfig[i].nAllowBits = 0;
	ServerConfig.GroupConfig[i].bAllowZeroBits = false;
end

ServerConfig.GroupConfig[1].nAllowBits = 2;
ServerConfig.GroupConfig[2].nAllowBits = 4;