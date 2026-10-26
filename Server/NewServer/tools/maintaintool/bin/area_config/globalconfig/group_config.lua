ServerConfig.GroupConfig = {};

for i = 0, MAX_SERVER_GROUP_COUNT - 1 do
	ServerConfig.GroupConfig[i] = {};
	ServerConfig.GroupConfig[i].nMaxRoleCount = 0;
	ServerConfig.GroupConfig[i].bPrecreateRole = false;
	ServerConfig.GroupConfig[i].szStartDate = "2020-01-01";
	ServerConfig.GroupConfig[i].dwStartDate = 0;

	ServerConfig.GroupConfig[i].nMappedGroupID = 0;
	ServerConfig.GroupConfig[i].bClearGlobalData = false;
end
