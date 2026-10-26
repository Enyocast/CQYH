LoadPackage("gameworld.pkg");
LoadPackage("role.pkg");
LoadPackage("item_bag.pkg");
LoadPackage("error_def.pkg");
LoadPackage("rank_list_def.pkg");
LoadPackage("chat_def.pkg");

Include("script/stringtable/stringtable.lh")

ITEM_ID = 93002;
ROLE_VAR_ID = 194;

g_oGameWorld = CGameWorld:GetInstance();

function del_item(owner, item_id, item_count)
	local ret;
	local roleid = get_ctx_role_id();
	local role = g_oGameWorld:FindValidRole(roleid);
	local itemBag = role:GetItemBag();

	local count = itemBag:GetItemCount(item_id, false);
	if count == 0 then
		return brvFail;
	end

	if item_count == 0 then
		item_count = count;
	end
	if item_count > count then
		return brvFail;
	end

	ret = itemBag:DeleteItemId(item_id, item_count, ITEMLOG_SCRIPT, false, 0x10000000);
	if ret ~= errSuccess then
		print("role "..role:GetName()..":"..role:GetObjID().." failed to submit item "..item_id.." count "..item_count);
		return brvFail;
	end

	local new_count = role:GetVariable(ROLE_VAR_ID) + item_count;
	role:SetVariable(ROLE_VAR_ID, new_count);
	role:UpdateRankListNode(rlActivity01, 0, new_count);

	return brvSuccess;
end

Include("script/newai/sub_tree/sub_tree.lh")
Include("script/newai/6161_DaHuiLangDuiJiang/main.uh")
