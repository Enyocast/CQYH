function SetAreaGroupConfig()
-- Region 1
	if ServerConfig.Common.nAreaID == 1 then
-------------------Guangmang
		if ServerConfig.MS.nInitGroup == Group1 then
			GameWorldConfig.nLevelLimit = 47;
			GameWorldConfig.dwClientOption = 15


-------------------Leiting
		elseif ServerConfig.MS.nInitGroup == Group2 then

------------------Lieyan
		elseif ServerConfig.MS.nInitGroup == Group3 then
			GameWorldConfig.nLevelLimit = 45;
			GameWorldConfig.dwClientOption = 15

------------------Jifeng
		elseif ServerConfig.MS.nInitGroup == Group4 then
			GameWorldConfig.nLevelLimit = 45;


-----------------Shushan
		elseif ServerConfig.MS.nInitGroup == Group5 then
			GameWorldConfig.nLevelLimit = 45;


---------------- Liuyun
		elseif ServerConfig.MS.nInitGroup == Group6 then
			GameWorldConfig.nLevelLimit = 45;
		end
	end
end
SetAreaGroupConfig();




function SetAreaGroupData()
	if ServerConfig.Common.nAreaID == 1 then
		if ServerConfig.MS.nInitGroup == Group1 then
			local scene_data = CDataManager_SCENE_DATA_:GetInstance():GetData(225);
			scene_data.nMinPortalLevel = 31;
		elseif ServerConfig.MS.nInitGroup == Group2 then

		elseif ServerConfig.MS.nInitGroup == Group3 then

		elseif ServerConfig.MS.nInitGroup == Group4 then

		elseif ServerConfig.MS.nInitGroup == Group5 then

		elseif ServerConfig.MS.nInitGroup == Group6 then

		end
	end
end
