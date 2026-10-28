Include("script/newai/robot/allan_basic.lua")
LoadPackage("title.pkg")
LoadPackage("role.pkg")
LoadPackage("asimov_user.pkg")

g_IsTitleDataInit = false;

TITLE_DATA_NUM = 0;
TITLE_DATA_TABLE = {}

g_TitleTemplate = CDataManager_TITLE_TEMPLATE_:GetInstance();

function title_data_init()

	if g_IsTitleDataInit == false then

		local index = 0;

		local title_data = g_TitleTemplate:GetFirstData();
		while title_data ~= nil do
			index = index + 1;
			TITLE_DATA_TABLE[index] = title_data;

			title_data = g_TitleTemplate:GetNextData();
		end

		TITLE_DATA_NUM = index;
		g_IsTitleDataInit = true;
	end
end


function performance_add_title(owner)
	title_data_init();

	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	local user =  CUserMgr:GetInstance():FindUser(role:GetSessionID());

	local index = math.random(1, TITLE_DATA_NUM);

	local ret = user:GMCommand("AddTitle(" .. TITLE_DATA_TABLE[index].m_nTemplateID .. ", 1)");
	--check(ret, "failed to send gm command");

    --local msg = recv_msg(5, role:GetSessionID(), protocol.g2c_add_title);
    --check(msg, "failed to recv g2c_add_title");
	--check(msg.nTitleID == TITLE_DATA_TABLE[index].m_nTemplateID, "failed to add title");
end



function performance_equip_title(owner)
	title_data_init();

	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	local user =  CUserMgr:GetInstance():FindUser(role:GetSessionID());


	local index = math.random(1, TITLE_DATA_NUM);

	local ret = role:GetTitle():IsTitleExist(TITLE_DATA_TABLE[index].m_nTemplateID);
	if ret then
		user:EquipTitle(TITLE_DATA_TABLE[index].m_nTemplateID);
	end

    --local msg = recv_msg(5, role:GetSessionID(), protocol.g2c_sync_equip_title);
    --check(msg, "failed to recv g2c_sync_equip_title");
	--check(msg.nEquipedTitleID == TITLE_DATA_TABLE[index].m_nTemplateID, "failed equip title"..msg.nEquipedTitleID);

end


function performance_unequip_title(owner)
	title_data_init();

	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	local user =  CUserMgr:GetInstance():FindUser(role:GetSessionID());

	local equip_title_id = role:GetTitle():GetEquipedTitleID();
	if equip_title_id ~= 0 then
		user:UnEquipTitle();
	end

    --local msg = recv_msg(5, role:GetSessionID(), protocol.g2c_sync_equip_title);
    --check(msg, "failed to recv g2c_sync_equip_title");
	--check(msg.nEquipedTitleID == 0, "failed to Unequip title");
end











