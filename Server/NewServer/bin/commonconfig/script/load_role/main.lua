LoadPackage("role.pkg");
LoadPackage("item.pkg");
LoadPackage("item_bag.pkg");
LoadPackage("char_def.pkg");
LoadPackage("spell_book.pkg");
LoadPackage("spell.pkg")
LoadPackage("quest_list.pkg")
LoadPackage("achievement_def.pkg")
LoadPackage("achievement_list.pkg")
LoadPackage("title.pkg")

function main(oRole)

	--local username = oRole:GetUserName();
	--oRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	--oRole:SetVariable(1009, 0);
	--
	----爵位称号上线全服提示
	--if oRole:GetTitle():FindTitle(57) then
	--	oRole:GetItemBag():BroadCastInGroup(1000036);--essBroadCastTitle1 公爵
	--	oRole:GetTitle():DeleteTitle(57,1);
	--end
	--if oRole:GetTitle():FindTitle(56) then
	--	oRole:GetItemBag():BroadCastInGroup(1000037);--essBroadCastTitle1 侯爵
	--	oRole:GetTitle():DeleteTitle(56,1);
	--end
	--if oRole:GetTitle():FindTitle(55) then
	--	oRole:GetItemBag():BroadCastInGroup(1000038);--essBroadCastTitle1 伯爵
	--	oRole:GetTitle():DeleteTitle(55,1);
	--end
	--if oRole:GetTitle():FindTitle(54) then
	--	oRole:GetItemBag():BroadCastInGroup(1000039);--essBroadCastTitle1 子爵
	--	oRole:GetTitle():DeleteTitle(54,1);
	--end
	--if oRole:GetTitle():FindTitle(53) then
	--	oRole:GetTitle():DeleteTitle(53,1);
	--end

end