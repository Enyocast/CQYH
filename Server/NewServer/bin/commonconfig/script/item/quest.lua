
QUEST_TABLE = {

};


for _,p in ipairs(QUEST_TABLE) do
	if _G[p.func] then
		print('detected duplicated quest function name '..p.func);
	end
	_G[p.func] = function(pItem, pRole)
		local oQuestList = pRole:GetQuestList();

		if (p.accept) then
			oQuestList:Accept(p.accept);
		elseif (p.complete) then
			oQuestList:Complete(p.complete);
		end

		return errSuccess;
	end
end
