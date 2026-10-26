LoadPackage("item_bag.pkg");
LoadPackage("item.pkg");
LoadPackage("role.pkg");
LoadPackage("attr_list.pkg")
LoadPackage("title.pkg")
LoadPackage("quest_list.pkg")
LoadPackage("error_def.pkg")
LoadPackage("char_def.pkg");
LoadPackage("hero.pkg");
LoadPackage("data_manager.pkg")
LoadPackage("gs_guild.pkg")
LoadPackage("guild_mgr.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("global_config.pkg")
LoadPackage("scene_def.pkg")
LoadPackage("spell_book.pkg")
LoadPackage("spell.pkg")
LoadPackage("scene.pkg")
LoadPackage("master.pkg")
LoadPackage("character.pkg");
LoadPackage("chat_def.pkg")
LoadPackage("rank_list_def.pkg");

-- 设置种子, 只需要全局设置一次
math.randomseed(os.time() * 1000 + os.clock() * 1000000);

g_oGameWorld = CGameWorld:GetInstance();


--[[
function OnUseIncreaseLuck(pItem, pRole)  	祝福油逻辑
function WeaponLevelUp(pItem, pRole)  		武器强化逻辑
function WeaponLevelUp1(pItem, pRole)		武器强化5必上6
function WeaponLevelUp2(pItem, pRole)		武器强化6必上7
function TeXiuLi(pItem, pRole)				特修卷逻辑		已废弃使用，特修逻辑写在了源码中
function TeXiuLi1(pItem, pRole)				披风解绑卷轴
function xingyun100(pItem, pRole)			玛法之力100点
function xingyun1(pItem, pRole)				玛法之力1点
function xingyun2(pItem, pRole)				玛法之力2点
function xingyun3(pItem, pRole)				玛法之力3点
function yuanbao88(pItem, pRole)				5元元宝券
function yuanbao5(pItem, pRole)				5元元宝券
function yuanbao10(pItem, pRole)			10元元宝券
function yuanbao50(pItem, pRole)			50元元宝券
function yuanbao100(pItem, pRole)			100元元宝券
function yuanbao500(pItem, pRole)			500元元宝券
function yuanbao1000(pItem, pRole)			1000元元宝券
function ZhiShenDan_40(pItem, pRole)		40级直升丹
function OnUseIncreaseLuck1(pItem, pRole)	直接把武器变成+7幸运值 不上电视的
function gongju1(pItem, pRole)				直接把武器变成+5幸运值 上电视的
function gongju2(pItem, pRole)				直接把武器变成+6幸运值 上电视的
function gongju3(pItem, pRole)				直接把武器变成+7幸运值 上电视的
function OnUseVip1(pItem, pRole)			VIP1
function OnUseVip2(pItem, pRole)			VIP2
function OnUseVip3(pItem, pRole)			VIP3
function SmallJinBi(pItem, pRole)			小金币包23333金币
function MidJinBi(pItem, pRole)				中金币包50000-200000 随机
function BigJinBi(pItem, pRole)				大金币包500000-2000000 随机
function chHeZi(pItem, pRole)				增加10000000经验
function LiaoShangYao(pItem, pRole)			增加疗伤药包 无限版
function ShengDanHeZi(pItem, pRole)			增加66666金币
function ZhiShenDan(pItem, pRole)			35直升丹
function DoubleJinYan10(pItem, pRole)		百分之10双倍经验丹
function DoubleJinYan500(pItem, pRole)		500W双倍经验丹
function woma_boss(pItem, pRole)			召唤沃玛教主全服提示版
function woma_boss1(pItem, pRole)			召唤沃玛教主全服不提示版
function zuma_boss(pItem, pRole)			召唤祖玛教主全服提示版
function zuma_boss1(pItem, pRole)			召唤祖玛教主全服不提示版
function hongmo_boss(pItem, pRole)			召唤虹魔教主全服提示版
function hongmo_boss1(pItem, pRole)			召唤虹魔教主全服不提示版
function chulongshen_boss(pItem, pRole)		召唤触龙神全服提示版
function chulongshen_boss1(pItem, pRole)	召唤触龙神全服不提示版
function lieyan_boss(pItem, pRole)			召唤烈焰恶魔全服提示版
function lieyan_boss1(pItem, pRole)			召唤烈焰恶魔全服不提示版
function chiyue_boss(pItem, pRole)			召唤赤月恶魔全服提示版
function chiyue_boss1(pItem, pRole)			召唤赤月恶魔全服不提示版
function molong_boss(pItem, pRole)			召唤魔龙教主全服提示版
function molong_boss1(pItem, pRole)			召唤魔龙教主全服不提示版
function zhuanyong1(pItem, pRole)			身上所有装备绑定（专用版本，专用绑定字段）
function zhuanyong2(pItem, pRole)			身上所有装备解绑（专用版本，专用绑定字段）
function zhuanyong3(pItem, pRole)			法师直身40并且学会所有技能并且是3级技能
function zhuanyong4(pItem, pRole)			用于查询身上装备绑定情况
function xingyun_boli(pItem, pRole)			把当前武器的幸运值剥离出来
function xingyun_chuancheng(pItem, pRole)	把剥离的幸运值传承到当前武器上
function qianghua_boli(pItem, pRole)		把当前武器的强化等级剥离出来
function qianghua_chuancheng(pItem, pRole)	把剥离的强化等级传承到当前武器上
function mingwen_boli(pItem, pRole)			把当前武器的铭文剥离出来
function mingwen_chuancheng(pItem, pRole)	把剥离的铭文传承到当前武器上
function xingyun_boli1(pItem, pRole)		--把当前项链的幸运值剥离出来
function xingyun_chuancheng1(pItem, pRole)	--把剥离的幸运值传承到当前项链上  5000的运2项链
function qifu(pItem, pRole)					--祈愿符逻辑，右键直接祈愿并公告给玩家当前节点
function xinshou_zhulibao(pItem, pRole)  	 --新手充值礼包
function tanshe_jiasubao(pItem, pRole)  	--弹射加速包
function qianghua_gongjubao(pItem, pRole)   --强化工具包
function zunxiang_libao(pItem, pRole)       --尊享礼包
function shengjidan_35(pItem, pRole)    	--升级丹1
function jingyan_kabao(pItem, pRole)   		--经验卡包
function zhuangbei_xilian(pItem, pRole)			--装备洗练
function xinyun_suipian(pItem, pRole)			--幸运碎片回收
function yb_dousha				--豆沙月饼
function yb_baiguo				--百果月饼
function yb_lianrong			--莲蓉月饼
function yb_xianrou				--鲜肉月饼
function VIP_summonnpc			--VIP刷怪
function PaoDian1  --泡点
function PaoDian2
function PaoDian3
function PaoDian4
function YaoQing_LiBao
function huigui_mingwen
function luandou_libao1
function zhanyue_jibu
function wuqi_zhuanyi
function xianglian_zhuanyi


]]--

--使用后删除道具，用于某些任务物品
function Deleteitem(pItem, pRole)
	return 1;  -- success
end

function xinyun_suipian(pItem, pRole)
	local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,100,true,0,0);
	return errSuccess;
end

-- 豆沙月饼 (100000经验值)
function yb_dousha(pItem, pRole)
	pRole:AddExp(81500, false,false);
	local msg = "玩家"..pRole:GetName() .. "使用豆沙月饼获得100000经验值！"
	local index = math.random(1,3);
	if index == 1 then
		pRole:AddExp(100000, false,false);
		pRole:GetScene():Say(pRole:GetObjID(), cltNormal,msg );
	end
	return errSuccess;	 
end	

-- 百果月饼 (81500金币)
function yb_baiguo(pItem, pRole)
	pRole:AddExp(81500, false,false);
	local msg = "玩家"..pRole:GetName() .. "使用百果月饼获得81500金币！"
	local index = math.random(1,5);
	if index <= 2 then
		pRole:GetItemBag():AddMoney(1, 81500, MONEYLOG_PACKAGE, 0,0);
		pRole:GetScene():Say(pRole:GetObjID(), cltNormal,msg );
	end
	return errSuccess;
end	

-- 莲蓉月饼 (100元宝)
function yb_lianrong(pItem, pRole)
	pRole:AddExp(81500, false,false);
	local msg = "玩家"..pRole:GetName() .. "使用莲蓉月饼获得[元宝]*100！"
	local username = pRole:GetUserName();
	local index = math.random(1,20);
	if index <= 7 then
		pRole:GetItemBag():ChangeYuanbao(username,100,true,2800009,1);
		pRole:GetScene():Say(cctServer, cltLighting,msg );
	end
	return errSuccess;
end	

-- 鲜肉月饼 (1000元宝)
function yb_xianrou(pItem, pRole)
	pRole:AddExp(81500, false,false);
	local msg = "玩家"..pRole:GetName() .. "使用鲜肉获得1000元宝！"
	local msg1 = "玩家"..pRole:GetName() .. "使用鲜肉获得稀有物品猩红之月！"
	local username = pRole:GetUserName();
	local index = math.random(1,10);
	if index == 1 then
		pRole:GetItemBag():ChangeYuanbao(username,1000,true,2800110,1);
		pRole:GetScene():Say(cctServer, cltLighting,msg1);
	elseif index > 5 then
		pRole:GetItemBag():AddItem(2800111, 1, ITEMLOG_SCRIPT, 0, false);
	end
	return errSuccess;
end	

-- 使用祝福油
function OnUseIncreaseLuck(pItem, pRole)
	local bag = pRole:GetItemBag();
	
	-- 获取当前佩戴武器对象
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if (weapon == nil) then
		return errItemNotFound;
	end
	
	-- 装备模板
	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(weapon.m_iteminfo.m_nTemplateID);
	
	if (equip_data == nil) then
		return errItemUnknown;
	end

	-- 当前武器幸运值
	local current_luck = weapon.m_iteminfo.m_byLuck;
	if (current_luck >= 7) then
		return errItemMaxLuck;
	end

	-- 当前是诅咒, 则必定成功
	if (current_luck <= 0) then
		bag:IncreaseWeaponLuck(1);
		return errSuccess;
	end
	
	-- 自己写的代码, 权重算法
	--[[
	-- 成功率 (1 - 10000) (20%=2000, 35%=3500)
	local arr_success_rate = {}
	arr_success_rate[1] = 7000
	arr_success_rate[2] = 6000
	arr_success_rate[3] = 5000
	arr_success_rate[4] = 4000
	arr_success_rate[5] = 3000
	arr_success_rate[6] = 2000
	arr_success_rate[7] = 1000
	
	-- 获取 当前判断概率
	local check_rate = arr_success_rate[current_luck + 1];
	
	-- 获取 随机数
	local random_num = math.random(10000);
	
	-- print("current_luck = "..current_luck.." check_rate = "..check_rate.." random_num = "..random_num);
	
	-- 20分之1概率, 幸运减少1
	if random_num <= 500 then
		bag:IncreaseWeaponLuck(-1);
		return errSuccess;
	end
	
	-- 成功
	if random_num < check_rate then
		bag:IncreaseWeaponLuck(1);
		return errSuccess;
	end
	]]--
	
	-- 判断 祝福油节点
	local luck_root = pRole:GetLuckRootCount();
	
	-- 达到 5000以上, 直接+7
	if luck_root >= 5000 then
		bag:SetWeaponLuck(7);
		return errSuccess;
	end
	
	
	-- 官方原代码 (概率非常低)
	-- 20分之1概率, 幸运减少1
	if math.random(20) == 1 then
		bag:IncreaseWeaponLuck(-1);
		return errSuccess;
	end
	
	-- 计算修正数值 (使用装备的"攻击数值", 计算出来的"修正数值")
	local factor = math.abs(equip_data.m_nFixAttr[1] - equip_data.m_nFixAttr[0]) / 5 + 0.5;
	-- print("factor == "..factor);
	
	-- 增加幸运值 (幸运 < 3)
	if (current_luck < 3 and math.random(factor + 6) == 1) then
		bag:IncreaseWeaponLuck(1);
		return errSuccess;
	end
	
	-- 增加幸运值 (幸运 < 5 && 幸运 > 2)
	if (current_luck < 5 and current_luck > 2 and math.random(5 * factor + 30) == 1) then
		bag:IncreaseWeaponLuck(1);
		return errSuccess;
	end
	
	-- 增加幸运值 (幸运 > 4)
	if (current_luck > 4 and math.random(5 * factor + 30) == 1) then
		bag:IncreaseWeaponLuck(1);
		
		-- 上电视
		local new_luck = weapon.m_iteminfo.m_byLuck;
		if new_luck >= 5 then
			local msg_luck = string.format("玩家[%s]的武器获得[幸运+%d]", pRole:GetName(), weapon.m_iteminfo.m_byLuck);
			-- print("msg_luck: "..msg_luck);
			pRole:Say(cctServer, cltTvShow, msg_luck);
		end
		
		return errSuccess;
	end
	
	-- 无变化
	bag:IncreaseWeaponLuck(0);
	
	return errSuccess;
end

-- 使用 高级祝福油
function OnUseIncreaseLuckAdvanced(pItem, pRole)
	local bag = pRole:GetItemBag();
	
	-- 获取当前佩戴武器对象
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if (weapon == nil) then
		return errItemNotFound;
	end
	
	-- 装备模板
	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(weapon.m_iteminfo.m_nTemplateID);
	
	if (equip_data == nil) then
		return errItemUnknown;
	end

	-- 当前武器幸运值
	local current_luck = weapon.m_iteminfo.m_byLuck;
	-- print("current_luck: "..current_luck);
	if (current_luck >= 7) then
		return errItemMaxLuck;
	end
	
	bag:IncreaseWeaponLuck(1);
	
	-- 上电视
	local new_luck = weapon.m_iteminfo.m_byLuck;
	if new_luck >= 5 then
		local msg_luck = string.format("玩家[%s]的武器获得[幸运+%d]", pRole:GetName(), weapon.m_iteminfo.m_byLuck);
		-- print("msg_luck: "..msg_luck);
		pRole:Say(cctServer, cltTvShow, msg_luck);
	end
	
	return errSuccess;
end

function OnUseIncreaseLuck2(pItem, pRole)
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
		if (weapon == nil) then
			return errItemNotFound;
		end
	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(weapon.m_iteminfo.m_nTemplateID);
		if (equip_data == nil) then
			return errItemUnknown;
		end
	local current_luck = weapon.m_iteminfo.m_byLuck;
		if (current_luck >= 7) then
			return errItemMaxLuck;
		end
		bag:IncreaseWeaponLuck(1);
		return errSuccess;

	
	
end

function WeaponLevelUp(pItem, pRole)
	local bag = pRole:GetItemBag();
	local FreeSolts = bag:GetFreeSlots(CONSLOT_DEFAULT);
	if FreeSolts == 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "背包已满，使用失败.");
		return errItemBagFull;	
	end
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴武器在使用此物品.");
		return errItemNoConsumeUse;
	end
	local cur_attr =  weapon.m_iteminfo.m_byLevelupPhyPoint + weapon.m_iteminfo.m_byLevelupMagPoint + weapon.m_iteminfo.m_byLevelupTaoPoint;
	if cur_attr > 6 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "您的武器已经强化到了目前的最高等级，无法再次强化！");
		return errItemNoConsumeUse;
	end
	local count = bag:GetItemCount(2800064, false);--强化油
	local count1 = bag:GetItemCount(2800065, false);--祖玛精华
	local money = bag:GetMoney(1);
	if money < 100000 then
		return errItemNotEnoughMoneytype02;
	end
	local result;
--	if count < 1 or count1 < 1 then
--		return errItemNotEnough;
--	end
--	bag:DeleteItemId(2800065, 1, ITEMLOG_EQUIP_LEVELUP,false,0);
	if cur_attr < 3 then
		result = bag:WeaponLevelUp(150);
	elseif cur_attr < 4 then
		result = bag:WeaponLevelUp(18); 
	elseif cur_attr < 5 then
		result = bag:WeaponLevelUp(5); 
	elseif cur_attr < 6 then
		result = bag:WeaponLevelUp(10);
	elseif cur_attr < 7 then
		result = bag:WeaponLevelUp(18);
	end
	return result;
end
function WeaponLevelUp1(pItem, pRole)--5必上6
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴武器在使用此物品.");
		return errItemNoConsumeUse;
	end
	local cur_attr =  weapon.m_iteminfo.m_byLevelupPhyPoint + weapon.m_iteminfo.m_byLevelupMagPoint + weapon.m_iteminfo.m_byLevelupTaoPoint;
	if cur_attr ~= 5 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "您必须带有+5的武器才能使用此物品，不然会武器承受不了强大的神龙之血！");
		return errItemNoConsumeUse;
	end
	result = bag:WeaponLevelUp(200);
	return result;
end
function WeaponLevelUp2(pItem, pRole)--6必上7
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴武器在使用此物品.");
		return errItemNoConsumeUse;
	end
	local cur_attr =  weapon.m_iteminfo.m_byLevelupPhyPoint + weapon.m_iteminfo.m_byLevelupMagPoint + weapon.m_iteminfo.m_byLevelupTaoPoint;
	if cur_attr ~= 6 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "您必须带有+6的武器才能使用此物品，不然会武器承受不了强大的圣龙之血！");
		return errItemNoConsumeUse;
	end
	result = bag:WeaponLevelUp(200);
	return result;
end
function TeXiuLi(pItem, pRole)
	local bag      = pRole:GetItemBag();
	local weapon   = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	local body     = bag:GetItem(CONSLOT_EQUIPPED, NES_BODY);
	local bank     = bag:GetItem(CONSLOT_EQUIPPED, NES_BACK);
	local head     = bag:GetItem(CONSLOT_EQUIPPED, NES_HEAD);
	local shoulder = bag:GetItem(CONSLOT_EQUIPPED, NES_SHOULDER);
	local arm      = bag:GetItem(CONSLOT_EQUIPPED, NES_ARM);
	local waist    = bag:GetItem(CONSLOT_EQUIPPED, NES_WAIST);
	local foot     = bag:GetItem(CONSLOT_EQUIPPED, NES_FOOT);
	local neck     = bag:GetItem(CONSLOT_EQUIPPED, NES_NECK);
	local finger_L = bag:GetItem(CONSLOT_EQUIPPED, NES_FINGER_L);
	local finger_R = bag:GetItem(CONSLOT_EQUIPPED, NES_FINGER_R);
	local wrist_L  = bag:GetItem(CONSLOT_EQUIPPED, NES_WRIST_L);
	local wrist_R  = bag:GetItem(CONSLOT_EQUIPPED, NES_WRIST_R);
	
	if weapon ~= nil then
		if weapon.m_iteminfo.m_nTemplateID == 199900018 or  weapon.m_iteminfo.m_nTemplateID == 199900019 or weapon.m_iteminfo.m_nTemplateID == 199900021 then
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "特殊装备不允许修理。");
			return	errItemNoConsumeUse
		end
		if weapon.m_iteminfo.m_nMaxDur > 32000 then
			weapon.m_iteminfo.m_nCurDur = 32000;
		else
			weapon.m_iteminfo.m_nCurDur = weapon.m_iteminfo.m_nMaxDur;
		end
	end
	if body  ~= nil then
		if body.m_iteminfo.m_nMaxDur > 32000 then
			body.m_iteminfo.m_nCurDur = 32000;
		else
			body.m_iteminfo.m_nCurDur = body.m_iteminfo.m_nMaxDur;
		end
	end
	if bank  ~= nil then
		if bank.m_iteminfo.m_nMaxDur > 32000 then
			bank.m_iteminfo.m_nCurDur = 32000;
		else
			bank.m_iteminfo.m_nCurDur = bank.m_iteminfo.m_nMaxDur;
		end
	end
	if head ~= nil then
		if head.m_iteminfo.m_nMaxDur > 32000 then
			head.m_iteminfo.m_nCurDur = 32000;
		else
			head.m_iteminfo.m_nCurDur = head.m_iteminfo.m_nMaxDur;
		end
	end
	if shoulder ~= nil then
		if shoulder.m_iteminfo.m_nMaxDur > 32000 then
			shoulder.m_iteminfo.m_nCurDur = 32000;
		else
			shoulder.m_iteminfo.m_nCurDur = shoulder.m_iteminfo.m_nMaxDur;
		end
	end
	if arm ~= nil then
		if arm.m_iteminfo.m_nMaxDur > 32000 then
			arm.m_iteminfo.m_nCurDur = 32000;
		else
			arm.m_iteminfo.m_nCurDur = arm.m_iteminfo.m_nMaxDur;
		end
	end
	if waist ~= nil then
		if waist.m_iteminfo.m_nMaxDur > 32000 then
			waist.m_iteminfo.m_nCurDur = 32000;
		else
			waist.m_iteminfo.m_nCurDur = waist.m_iteminfo.m_nMaxDur;
		end
	end
	if foot ~= nil then
		if foot.m_iteminfo.m_nMaxDur > 32000 then
			foot.m_iteminfo.m_nCurDur = 32000;
		else
			foot.m_iteminfo.m_nCurDur = foot.m_iteminfo.m_nMaxDur;
		end
	end
	if neck ~= nil then
		if neck.m_iteminfo.m_nMaxDur > 32000 then
			neck.m_iteminfo.m_nCurDur = 32000;
		else
			neck.m_iteminfo.m_nCurDur = neck.m_iteminfo.m_nMaxDur;
		end
	end
	if finger_L ~= nil then
		if finger_L.m_iteminfo.m_nMaxDur > 32000 then
			finger_L.m_iteminfo.m_nCurDur = 32000;
		else
			finger_L.m_iteminfo.m_nCurDur = finger_L.m_iteminfo.m_nMaxDur;
		end
	end
	if finger_R ~= nil then
		if finger_R.m_iteminfo.m_nMaxDur > 32000 then
			finger_R.m_iteminfo.m_nCurDur = 32000;
		else
			finger_R.m_iteminfo.m_nCurDur = finger_R.m_iteminfo.m_nMaxDur;
		end
	end
	if wrist_L ~= nil then
		if wrist_L.m_iteminfo.m_nMaxDur > 32000 then
			wrist_L.m_iteminfo.m_nCurDur = 32000;
		else
			wrist_L.m_iteminfo.m_nCurDur = wrist_L.m_iteminfo.m_nMaxDur;
		end	
	end
	if wrist_R ~= nil then
		if wrist_R.m_iteminfo.m_nMaxDur > 32000 then
			wrist_R.m_iteminfo.m_nCurDur = 32000;
		else
			wrist_R.m_iteminfo.m_nCurDur = wrist_R.m_iteminfo.m_nMaxDur;
		end
	end
	return errSuccess;
end
function TeXiuLi1(pItem, pRole)--披风解绑卷轴
	local bag = pRole:GetItemBag();
	local bank	= bag:GetItem(CONSLOT_EQUIPPED, NES_BACK);
	if bank  == nil then
		return errItemNoConsumeUse
	end
	if bank.m_iteminfo.m_byBindType == 0 then
		bank.m_iteminfo.m_byBindType = 10;
	else
		bank.m_iteminfo.m_byBindType = 0;
	end
	return	errSuccess;
end
function xingyun100(pItem, pRole)--玛法之力100点
	local a = pRole:GetVariable(1023);
	a = a + 100;
	pRole:SetVariable(1023,a);
	return errSuccess;
end
function xingyun1(pItem, pRole)--玛法之力1点
	local a = pRole:GetVariable(1023);
	a = a + 1;
	pRole:SetVariable(1023,a);
	return errSuccess;
end
function xingyun2(pItem, pRole)--玛法之力2点
	local a = pRole:GetVariable(1023);
	a = a + 2;
	pRole:SetVariable(1023,a);
	return errSuccess;
end
function xingyun3(pItem, pRole)--玛法之力3点
	local a = pRole:GetVariable(1023);
	a = a + 3;
	pRole:SetVariable(1023,a);
	return errSuccess;
end


function yuanbao1(pItem, pRole)--元宝1
	local username = pRole:GetUserName();
	local ret = pRole:GetItemBag():ChangeYuanbao(username,100,true,1800058,1);
	return errSuccess;
end
function yuanbao88(pItem, pRole)--元宝88
	local username = pRole:GetUserName();
	local ret = pRole:GetItemBag():ChangeYuanbao(username,8800,true,1800058,1);
	return errSuccess;
end
function yuanbao5(pItem, pRole)--元宝5
	local username = pRole:GetUserName();
	local ret = pRole:GetItemBag():ChangeYuanbao(username,500,true,2800081,1);
	return errSuccess;
end
function yuanbao10(pItem, pRole)--元宝10
	local username = pRole:GetUserName();
	local ret = pRole:GetItemBag():ChangeYuanbao(username,1000,true,2800082,1);
	return errSuccess;
end
function yuanbao50(pItem, pRole)--元宝50
	local username = pRole:GetUserName();
	local ret = pRole:GetItemBag():ChangeYuanbao(username,5000,true,2800083,1);
	return errSuccess;
end
function yuanbao100(pItem, pRole)--元宝100
	local username = pRole:GetUserName();
	local ret = pRole:GetItemBag():ChangeYuanbao(username,10000,true,2800077,1);
	return errSuccess;
end
function yuanbao500(pItem, pRole)--元宝500
	local username = pRole:GetUserName();
	local ret = pRole:GetItemBag():ChangeYuanbao(username,50000,true,2800084,1);
	return errSuccess;
end
function yuanbao1000(pItem, pRole)--元宝1000
	local username = pRole:GetUserName();
	local ret = pRole:GetItemBag():ChangeYuanbao(username,100000,true,2800085,1);
	return errSuccess;
end
function ZhiShenDan_40(pItem, pRole)--40级直升丹
	--if pRole:GetLevel() > 39 then
	--	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "必须小于40级才能使用此物品");
	--	return errItemNoConsumeUse;
	--end
	pRole:SetLevel(50);
	return errSuccess;
end
function OnUseIncreaseLuck1(pItem, pRole)
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if (weapon == nil) then
		return errItemNotFound;
	end

	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(weapon.m_iteminfo.m_nTemplateID);
	if (equip_data == nil) then
		return errItemUnknown;
	end

	local current_luck = weapon.m_iteminfo.m_byLuck;
	if (current_luck >= 7) then
		return errItemMaxLuck;
	end
	weapon.m_iteminfo.m_byLuck = 7;
	return errSuccess;
end
function gongju1(pItem, pRole)
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if (weapon == nil) then
		return errItemNotFound;
	end

	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(weapon.m_iteminfo.m_nTemplateID);
	if (equip_data == nil) then
		return errItemUnknown;
	end

	local current_luck = weapon.m_iteminfo.m_byLuck;
	if (current_luck >= 7) then
		return errItemMaxLuck;
	end
	bag:IncreaseWeaponLuck(5 - current_luck);
	return errSuccess;
end
function gongju2(pItem, pRole)
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if (weapon == nil) then
		return errItemNotFound;
	end

	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(weapon.m_iteminfo.m_nTemplateID);
	if (equip_data == nil) then
		return errItemUnknown;
	end

	local current_luck = weapon.m_iteminfo.m_byLuck;
	if (current_luck >= 7) then
		return errItemMaxLuck;
	end
	bag:IncreaseWeaponLuck(6 - current_luck);
	return errSuccess;
end
function gongju3(pItem, pRole)
		local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if (weapon == nil) then
		return errItemNotFound;
	end

	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(weapon.m_iteminfo.m_nTemplateID);
	if (equip_data == nil) then
		return errItemUnknown;
	end

	local current_luck = weapon.m_iteminfo.m_byLuck;
	if (current_luck >= 7) then
		return errItemMaxLuck;
	end
	bag:IncreaseWeaponLuck(7 - current_luck);
	return errSuccess;
end

function gongju4(pItem, pRole)
	local bag = pRole:GetItemBag();
	local item = bag:GetItem(CONSLOT_DEFAULT,0);
	if item == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请在背包栏第一个放置装备才可使用此物品。");
		return errItemNotFound;
	end
	if item.m_pTemplate.m_byType ~= ITEMTYPE_EQUIP then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "背包第一格必须是装备才能使用此物品。");	
		return errItemNotFound;
	end
	bag:EquipRebirth();
	return errSuccess;
end
--vip
function OnUseVip1(pItem, pRole)
	pRole:GetScene():Say(pRole:GetObjID(), cltLighting, "恭喜您成为白银会员，你拥有以下特权：聚灵珠60%效率，每日食用上限：6个，召唤物存活时间+1小时，宠物下线保护5分钟，商店折扣-1%，个人爆率+5%，额外经验获取+5%，魔虫窟次数+1。");
    	return pRole:SubscribeVIP(1,31);--修改了VIP时间限制改成了1月by.xxp
end

function OnUseVip2(pItem, pRole)
	local VIP = pRole:GetVIPLevel();
	local username = pRole:GetUserName();
	local cDateCurrectTime = os.date("*t",os.time());
	local cDateTodayTime = os.time({year=cDateCurrectTime.year, month=cDateCurrectTime.month, day=cDateCurrectTime.day, hour=0,min=0,sec=0});
	--[[if VIP == 1 then
		local expirytime = pRole:GetVIPTime(1);
		local days = (expirytime - cDateTodayTime) / 86400;
		pRole:GetItemBag():ChangeYuanbao(username,days * 200,true,2102 , 1);
	end
	if VIP >= 2 then
		pRole:GetItemBag():ChangeYuanbao(username, 25000,true,2102,1);
		return errSuccess;
	end]]--
	pRole:GetScene():Say(pRole:GetObjID(), cltLighting, "恭喜您成为黄金会员，你拥有以下特权：聚灵珠70%效率，每日食用上限：7个，召唤物存活时间+1.5小时，宠物下线保护30分钟，商店折扣-2.5%，聚宝盆双倍金币产出概率+20%，个人爆率+10%，额外经验获取+8%，魔虫窟次数+2。");
    return pRole:SubscribeVIP(2,31);
end
function OnUseVip3(pItem, pRole)
	local VIP = pRole:GetVIPLevel();
	local username = pRole:GetUserName();
	local cDateCurrectTime = os.date("*t",os.time());
	local cDateTodayTime = os.time({year=cDateCurrectTime.year, month=cDateCurrectTime.month, day=cDateCurrectTime.day, hour=0,min=0,sec=0});
	--[[if VIP == 1 then
		local expirytime = pRole:GetVIPTime(1);
		local days = (expirytime - cDateTodayTime) / 86400;
		pRole:GetItemBag():ChangeYuanbao(username,days * 200,true,2103,1);
	end
	if VIP == 2 then
		local expirytime = pRole:GetVIPTime(2);
		local days = (expirytime - cDateTodayTime) / 86400;
		pRole:GetItemBag():ChangeYuanbao(username,days * 900,true,2103,1);
	end]]--
	pRole:GetScene():Say(pRole:GetObjID(), cltLighting, "恭喜您成为钻石会员，你拥有以下特权：聚灵珠80%效率，每日食用上限：8个，召唤物存活时间+2小时，宠物下线保护60分钟，商店折扣-5%，个人爆率+15%，聚宝盆双倍金币产出概率+40%，个额外经验获取+10%，魔虫窟次数+3。");
    return pRole:SubscribeVIP(3,31);
end

function SmallJinBi(pItem, pRole)
	return	pRole:GetItemBag():AddMoney(1, 150000, MONEYLOG_PACKAGE, 0,0);	
end

function MidJinBi(pItem, pRole)
		local a = tostring(os.clock()):reverse():sub(1, 3)
		math.randomseed(a);
		local b = math.random(1,a);
		local c =b + os.time();
		math.randomseed(tostring(c):reverse():sub(1, 5));
		local d = math.random(50000,200000);
	return	pRole:GetItemBag():AddMoney(1, d, MONEYLOG_PACKAGE, 0,0);	
end
function BigJinBi(pItem, pRole)
	return	pRole:GetItemBag():AddMoney(1, 500000, MONEYLOG_PACKAGE, 0,0);	
end
function chHeZi(pItem, pRole)
	pRole:AddExp(10000000, false,false);
	return errItemNoConsumeUse;
end
function LiaoShangYao(pItem, pRole)
		pRole:GetItemBag():AddItem(353, 6, ITEMLOG_REAL_MONEY_SHOP, 0, false);
		return pRole:GetItemBag():AddItem(1800017, 1, ITEMLOG_REAL_MONEY_SHOP, 0, false);
end
function ShengDanHeZi(pItem, pRole)
	pRole:GetItemBag():AddItem(111001, 500, MONEYLOG_PACKAGE, 0,0);
	return	pRole:GetItemBag():AddItem(1800013, 1, MONEYLOG_PACKAGE, 0,0);
end
function ZhiShenDan(pItem, pRole)
	--[[if pRole:GetVIPLevel() < 1 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请使用白银VIP药水之后再使用次物品");
		return errItemNoConsumeUse;
	end]]--
	
	if pRole:GetLevel() > 34 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "必须小于35级才能使用此物品");
		return errItemNoConsumeUse;
	end
	pRole:SetLevel(35);
	
	return errSuccess;
	
end
function DoubleJinYan10(pItem, pRole)
	local level = pRole:GetLevel()
	if level < 35 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "该物品必须高于35级有效。");
		return errItemNoConsumeUse;
	end

	local level = pRole:GetLevel();
	local nLevel = CDataManager_ROLE_LEVEL_DATA_:GetInstance():GetData(level);
	local MaxExp = nLevel.m_nMaxExp;
	pRole:AddExtraExp(MaxExp / 10);

	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "你已获得当前等级百分之十的双倍经验,赶快去升级吧!");
	return	errSuccess;
end
function DoubleJinYan500(pItem, pRole)
	pRole:AddExtraExp(5000000)
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "你已获得500万的双倍经验,赶快去升级吧!");	
	return	errSuccess;
end

function DoubleJinYan100(pItem, pRole)
	pRole:AddExtraExp(1000000)
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "你已获得100万的双倍经验,赶快去升级吧!");	
	return	errSuccess;
end

function woma_boss(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end
		
	nTemplateID = 5278
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	
	local msg = "玩家"..pRole:GetName() .. "在"..mapname.."召唤了一只沃玛教主！"
	pRole:Say(cctServer, cltLighting, msg);
	return	errSuccess;
end
function woma_boss1(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end

	nTemplateID = 5278
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	
	return	errSuccess;
end
function zuma_boss(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end

	nTemplateID = 5301
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	local msg = "玩家"..pRole:GetName() .. "在"..mapname.."召唤了一只祖玛教主！"
	pRole:Say(cctServer, cltLighting, msg);
	return	errSuccess;
end

function zuma_boss1(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end
	nTemplateID = 5301
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	
	return	errSuccess;
end

function hongmo_boss(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end

	nTemplateID = 5297
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	local msg = "玩家"..pRole:GetName() .. "在"..mapname.."召唤了一只虹魔教主！"
	pRole:Say(cctServer, cltLighting, msg);
	return	errSuccess;
end

function hongmo_boss1(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end

	nTemplateID = 5297
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	
	return	errSuccess;
end

function chulongshen_boss(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end

	nTemplateID = 5287
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	local msg = "玩家"..pRole:GetName() .. "在"..mapname.."召唤了一只触龙神！"
	pRole:Say(cctServer, cltLighting, msg);
	return	errSuccess;
end

function chulongshen_boss1(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end
	nTemplateID = 5287
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	
	return	errSuccess;
end

function lieyan_boss(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end

	nTemplateID = 5500
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	local msg = "玩家"..pRole:GetName() .. "在"..mapname.."召唤了一只烈焰恶魔！"
	pRole:Say(cctServer, cltLighting, msg);
	return	errSuccess;
end

function lieyan_boss1(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end
	nTemplateID = 5500
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	
	return	errSuccess;
end

function chiyue_boss(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end

	nTemplateID = 5306
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	local msg = "玩家"..pRole:GetName() .. "在"..mapname.."召唤了一赤月恶魔！"
	pRole:Say(cctServer, cltLighting, msg);
	return	errSuccess;
end

function chiyue_boss1(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end
	nTemplateID = 5306
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	
	return	errSuccess;
end

function molong_boss(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end

	nTemplateID = 5283
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	local msg = "玩家"..pRole:GetName() .. "在"..mapname.."召唤了一魔龙教主！"
	pRole:Say(cctServer, cltLighting, msg);
	return	errSuccess;
end

function molong_boss1(pItem, pRole)
	local map = pRole:GetSceneTempID()
	local mapname;
		if map == 153 then 
			mapname = "矿区二层"
		elseif map == 154 then
			mapname = "矿区三层"
		elseif map == 148 then
			mapname = "死亡峡谷一层"
		elseif map == 201 then
			mapname = "死亡峡谷二层"
		elseif map == 157 then
			mapname = "死亡峡谷三层"
		elseif map == 159 then
			mapname = "石墓二层"
		elseif map == 160 then
			mapname = "石墓三层"
		elseif map == 161 then
			mapname = "石墓四层"
		elseif map == 146 then
			mapname = "沃玛寺庙一层"
		elseif map == 155 then
			mapname = "沃玛寺庙二层"
		elseif map == 180 then
			mapname = "祖玛寺庙一层"
		elseif map == 167 then
			mapname = "祖玛寺庙二层"
		elseif map == 168 then
			mapname = "祖玛寺庙三层"
		elseif map == 169 then
			mapname = "祖玛寺庙四层"
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请到规定的地图使用此物品.");	
			return errItemNoConsumeUse;
		end
	nTemplateID = 5283
    	local oScene = pRole:GetScene();
	local oNpc = oScene:SpawnNpc(nTemplateID, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
	if oNpc == nil then
		return errItemNoConsumeUse;
	end
	
	return	errSuccess;
end

function zhuanyong1(pItem, pRole)
	pRole:SetVariable(1016,1024);
	return  errSuccess;	
end

function zhuanyong2 (pItem, pRole)
	pRole:SetVariable(1016,0);
	return  errSuccess;	
end

function zhuanyong3 (pItem, pRole)
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴武器在使用此物品.");
		return errItemNoConsumeUse;
	end
	local cur_attr =  weapon.m_iteminfo.m_byLevelupPhyPoint + weapon.m_iteminfo.m_byLevelupMagPoint + weapon.m_iteminfo.m_byLevelupTaoPoint;
	result = bag:WeaponLevelUp(200);
	return result;
end

function zhuanyong4(pItem, pRole)			--用于查询身上装备绑定情况
	local var = pRole:GetVariable(1016);	
	if var == 1024 then
		pRole:GetScene():Say(pRole:GetObjID(), cltNormal,"已帮定");
	else
		pRole:GetScene():Say(pRole:GetObjID(), cltNormal,"未帮定");
	end
	return  errItemNoConsumeUse;	
end


function xingyun_boli(pItem, pRole)			--把当前武器的幸运值剥离出来
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴需要剥离的武器再使用此物品.");
		return errItemNoConsumeUse;
	end
	local luck = weapon.m_iteminfo.m_byLuck;
	if luck <= 0 or luck > 7 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "要剥离的武器的幸运值不合法");
		return errItemNoConsumeUse;
	end
	if pRole:GetVariable(1021) ~= 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "您已经剥离过武器的幸运值，请先传承后再使用。");
		return errItemNoConsumeUse;
	end
	pRole:SetVariable(1021,luck);
	bag:Refreshitem(NES_MAIN_HAND,1);
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "武器的幸运值剥离成功，请注意背包发放的武器幸运传承卷，带上新的武器后使用即可。");
	pRole:GetItemBag():AddItem(2800088, 1, ITEMLOG_SCRIPT, 0, false);
	return errSuccess;
end

function xingyun_chuancheng(pItem, pRole)	--把剥离的幸运值传承到当前武器上
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴需要传承的武器再使用此物品.");
		return errItemNoConsumeUse;
	end
	local luck = pRole:GetVariable(1021);
	if luck <= 0 or luck > 7 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "没有进行过武器幸运剥离，请先使用武器幸运剥离卷后再使用本物品");
		return errItemNoConsumeUse;
	end
	local current_luck = weapon.m_iteminfo.m_byLuck;
	if current_luck >= luck then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "当前佩戴武器的幸运值比传承的幸运值高，如果使用此物品将会覆盖掉原有幸运值。");
		return errItemNoConsumeUse;
	end
	weapon.m_iteminfo.m_byLuck = luck;
	bag:Refreshitem(NES_MAIN_HAND);
	pRole:SetVariable(1021,0);
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "武器幸运传承成功。");
	return errSuccess;
end

function qianghua_boli(pItem, pRole)		--把当前武器的强化等级剥离出来
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴需要剥离的武器再使用此物品.");
		return errItemNoConsumeUse;
	end
	
	if weapon.m_iteminfo.m_nTemplateID < 99900018 or 
	   weapon.m_iteminfo.m_nTemplateID > 99900033 or 
	   weapon.m_iteminfo.m_nTemplateID == 99900020 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "该物品只能剥离沃玛级别以上的武器。");
		return errItemNoConsumeUse;
	end
	
	local qianghua = weapon.m_iteminfo.m_byLevelupPhyPoint + 
	                weapon.m_iteminfo.m_byLevelupMagPoint + 
	                weapon.m_iteminfo.m_byLevelupTaoPoint;
	if qianghua < 7 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "当前佩戴的武器并没有强化满，无法剥离强化值。");
		return errItemNoConsumeUse;
	end
	if pRole:GetVariable(1020) ~= 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "您已经剥离过武器的强化值，请先传承后再使用。");
		return errItemNoConsumeUse;
	end
	pRole:SetVariable(1020,qianghua);
	bag:Refreshitem(NES_MAIN_HAND,2);
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "武器的强化值剥离成功，请注意背包发放的武器强化传承卷，带上新的武器后使用即可。");
	pRole:GetItemBag():AddItem(2800090, 1, ITEMLOG_SCRIPT, 0, false);
	return errSuccess;
end
function qianghua_chuancheng(pItem, pRole)	--把剥离的强化等级传承到当前武器上
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴需要传承的武器再使用此物品.");
		return errItemNoConsumeUse;
	end
	local qianghua = pRole:GetVariable(1020);
	if qianghua <= 0 or qianghua > 10 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "没有进行过武器传承剥离，请先使用武器强化剥离卷后再使用本物品");
		return errItemNoConsumeUse;
	end
	bag:WeaponLevelUp1(qianghua);
	pRole:SetVariable(1020,0);
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "武器强化传承成功。");
	return errSuccess;
end

function mingwen_boli(pItem, pRole)			--把当前武器的铭文剥离出来
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴需要剥离的武器再使用此物品.");
		return errItemNoConsumeUse;
	end
	local mingwen1 = weapon.m_iteminfo.m_wRune[0];
	local mingwen2 = weapon.m_iteminfo.m_wRune[1];
	if mingwen1 == 0 and mingwen2 == 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "当前武器并没有铭文，避免造成不必要浪费，请剥离带铭文的武器。");
		return errItemNoConsumeUse;
	end
	if pRole:GetVariable(1019) ~= 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "您已经剥离过武器的铭文，请先传承后再使用。");
		return errItemNoConsumeUse;
	end
	if pRole:GetVariable(1018) ~= 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "您已经剥离过武器的铭文，请先传承后再使用。");
		return errItemNoConsumeUse;
	end
	pRole:SetVariable(1019,mingwen1);
	pRole:SetVariable(1018,mingwen2);
	bag:Refreshitem(NES_MAIN_HAND,3);
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "武器的铭文剥离成功，请注意背包发放的武器铭文传承卷，带上新的武器后使用即可。");
	pRole:GetItemBag():AddItem(2800092, 1, ITEMLOG_SCRIPT, 0, false);
	return errSuccess;
	
end
function mingwen_chuancheng(pItem, pRole)	--把剥离的铭文传承到当前武器上
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴需要剥离的武器再使用此物品.");
		return errItemNoConsumeUse;
	end
	local mingwen1 = pRole:GetVariable(1019);
	local mingwen2 = pRole:GetVariable(1018);
	if mingwen1 == 0 and mingwen2 == 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "没有进行过武器铭文剥离，请先使用铭文剥离卷后再使用本物品");
		return errItemNoConsumeUse;
	end
	weapon.m_iteminfo.m_wRune[0] = mingwen1;
	weapon.m_iteminfo.m_wRune[1] = mingwen2;
	bag:Refreshitem(NES_MAIN_HAND);
	pRole:SetVariable(1019,0);
	pRole:SetVariable(1018,0);
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "武器铭文传承成功。");
	return errSuccess;
end

function xingyun_boli1(pItem, pRole)--把当前项链的幸运值剥离出来
	local bag = pRole:GetItemBag();
	local neck = bag:GetItem(CONSLOT_EQUIPPED, NES_NECK);
	if neck == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴项链再使用此物品.");
		return errItemNoConsumeUse;
	end
	local luck = neck.m_iteminfo.m_wRandomAttrID[0];
	if luck ~= 32080 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "幸运数值有问题，请联系客服。");
		return errItemNoConsumeUse;
	end
	if pRole:GetVariable(1017) ~= 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "您已经剥离过项链的属性，请先传承后再使用。");
		return errItemNoConsumeUse;
	end

	if neck.m_iteminfo.m_nTemplateID == 999200213 then
		pRole:SetVariable(1017,2);
	elseif neck.m_iteminfo.m_nTemplateID == 999200223 then
		pRole:SetVariable(1017,3);
	elseif neck.m_iteminfo.m_nTemplateID == 999200233 then
		pRole:SetVariable(1017,4);
	else
		pRole:SetVariable(1017,1);
	end
	bag:Refreshitem(NES_NECK,4);
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "项链的幸运值剥离成功，请注意背包发放的幸运传承卷，带上新的项链后使用传承卷即可，请谨慎操作。");
	pRole:GetItemBag():AddItem(2800098, 1, ITEMLOG_SCRIPT, 0, false);
	return errSuccess;
end

function xingyun_chuancheng1(pItem, pRole)	--把剥离的幸运值传承到当前项链上  5000的运2项链
	local bag = pRole:GetItemBag();
	local neck = bag:GetItem(CONSLOT_EQUIPPED, NES_NECK);
	if neck == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴项链再使用此物品.");
		return errItemNoConsumeUse;
	end
	local neckid = neck.m_iteminfo.m_nTemplateID;
	if neckid == 99920027 or neckid == 99920028 or neckid == 99920029 or neckid == 299920027 or neckid == 299920028 or neckid == 299920029 or neckid ==  99920032 or neckid ==  99920033 or neckid ==  99920034 or neckid == 99920030 then
		local luck = neck.m_iteminfo.m_wRandomAttrID[0];
		if luck == 32080 then
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "当前项链已经有运2属性，传承失败。");
			return errItemNoConsumeUse;
		end
		local necktype = pRole:GetVariable(1017);
		if necktype == 0 then
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请先进行剥离后再传承");
			return errItemNoConsumeUse;
		elseif necktype == 1 then
			bag:Refreshitem(NES_NECK,5);
		elseif necktype == 2 then
			if neckid == 99920027 or neckid == 299920027 or neckid ==  99920032 or neckid == 99920030 then
				bag:Refreshitem(NES_NECK,6);
			else
				pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "剥离下来的是攻击属性，避免属性损失，请使用战士的赤月级以上项链传承。");
				return errItemNoConsumeUse;	
			end
		elseif necktype == 3 then
			if neckid == 99920028 or neckid == 299920028 or neckid == 99920033 or neckid == 99920030 then
				bag:Refreshitem(NES_NECK,7);
			else
				pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "剥离下来的是魔法属性，避免属性损失，请使用法师的赤月级以上项链传承。");
				return errItemNoConsumeUse;	
			end
		elseif necktype == 4 then
			if neckid == 99920029 or neckid == 299920029  or neckid == 99920034 or neckid == 99920030 then
				bag:Refreshitem(NES_NECK,8);
			else
				pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "剥离下来的是道术属性，避免属性损失，请使用道士的赤月级以上项链传承。");
				return errItemNoConsumeUse;	
			end
		end
		pRole:SetVariable(1017,0);
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "项链幸运传承成功。");
		return errSuccess;
	else
		print(neck.m_iteminfo.m_nTemplateID);
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "只能传承到赤月级别以上的项链。");
		return errItemNoConsumeUse;
	end
end


function qifu(pItem, pRole)					--祈愿符逻辑，右键直接祈愿并公告给玩家当前节点
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "活动已结束。");
		return errItemNoConsumeUse;

	--[[local bag = pRole:GetItemBag();
	bag:GambleItem();
	local jiedian = bag:GetJieDian();
	local msg = "当前祈愿符节点为"..jiedian;
	pRole:GetScene():Say(pRole:GetObjID(), cltNormal,msg );
	return errItemNoConsumeUse;]]--
end

function zhuangbei_xilian(pItem, pRole)    --装备洗炼
	local username = pRole:GetUserName();
		pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);	
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_DEFAULT, 0);
	local itemid = weapon.m_iteminfo.m_nTemplateID;
	local bind = weapon.m_iteminfo.m_byBindType;
	local dur = weapon.m_iteminfo.m_nMaxDur;
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请将需要洗练的装备放在物品栏第一格再使用此物品.");
		return errItemNoConsumeUse;
	end
	if itemid == 999903261 or itemid == 999904261 or itemid == 999904361 or itemid == 999904461 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "护手过于强大，不允许洗练");
		return errItemNoConsumeUse;
	end
	local yuanbao = pRole:GetItemBag():GetMoney(3);--元宝
	local count1 = bag:GetItemCount(2800075, false);--沃玛精华
	if itemid == 199900018 or itemid == 199900019 or itemid == 199900021 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "此物品不能洗练回归系列装备。");
		return errItemNoConsumeUse;
	end
	if itemid < 59900001 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "此物品只能洗炼武器和装备。");
		return errItemNoConsumeUse;
	elseif bind == 10 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "绑定装备无法洗炼。");
		return errItemNoConsumeUse;
	elseif dur - weapon.m_iteminfo.m_nCurDur > 1000 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "未修理的装备无法洗炼。");
		return errItemNoConsumeUse;	
	elseif yuanbao < 300 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
		return errItemNoConsumeUse;
	elseif count1 < 3  then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "沃玛精华不足。");
		return errItemNoConsumeUse;
	end
	bag:DeleteItemPos(CONSLOT_DEFAULT,0,1,ITEMLOG_SCRIPT,0);
	bag:ChangeYuanbao(username,300,false,2800075,1);
	bag:DeleteItemId(2800075, 3, ITEMLOG_EQUIP_LEVELUP,false,0);
	bag:AddItem(itemid,1,ITEMLOG_SCRIPT,0,false);
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "洗炼成功。");
	return errSuccess;
end

function dakongshi(pItem, pRole)    --打孔石
	local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);	
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_DEFAULT, 0);
	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(weapon.m_iteminfo.m_nTemplateID);
	if weapon == nil or equip_data == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请将需要打孔的装备放在物品栏第一格再使用此物品.");
		return errItemNoConsumeUse;
	end
	local itemid = weapon.m_iteminfo.m_nTemplateID;
	local bind = weapon.m_iteminfo.m_byBindType;
	local dur = weapon.m_iteminfo.m_nMaxDur;
--	local yuanbao = pRole:GetItemBag():GetMoney(3);--元宝

	if weapon.m_iteminfo.m_nSoulID[0] ~= 0 or  weapon.m_iteminfo.m_nSoulID[1] ~= 0 or  weapon.m_iteminfo.m_nSoulID[2] ~= 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请把宝石拆除后再使用此物品。");
		return errItemNoConsumeUse;
	end

	if bind == 10 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "绑定装备无法打孔。");
		return errItemNoConsumeUse;
	elseif dur - weapon.m_iteminfo.m_nCurDur > 1000 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "未修理的装备无法打孔。");
		return errItemNoConsumeUse;	
--	elseif yuanbao < 1000 then
--		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
--		return errItemNoConsumeUse;
	end
	local ret = bag:GenerateSocket(false,1);
	if ret == 1 then 
--		bag:ChangeYuanbao(username,1000,false,91115,1);
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "打孔成功。");
	else
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "该装备打孔失败，物品和元宝不消耗。");
		return errItemNoConsumeUse;
	end
	return errSuccess;
end

function dakongshi_gonghui(pItem, pRole)    --公会打孔石
	local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);	
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_DEFAULT, 0);
	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(weapon.m_iteminfo.m_nTemplateID);
	if weapon == nil or equip_data == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请将需要打孔的装备放在物品栏第一格再使用此物品.");
		return errItemNoConsumeUse;
	end
	local itemid = weapon.m_iteminfo.m_nTemplateID;
	local bind = weapon.m_iteminfo.m_byBindType;
	local dur = weapon.m_iteminfo.m_nMaxDur;
--	local yuanbao = pRole:GetItemBag():GetMoney(3);--元宝

	if weapon.m_iteminfo.m_nSoulID[0] ~= 0 or  weapon.m_iteminfo.m_nSoulID[1] ~= 0 or  weapon.m_iteminfo.m_nSoulID[2] ~= 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请把宝石拆除后再使用此物品。");
		return errItemNoConsumeUse;
	end

	if bind == 10 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "绑定装备无法打孔。");
		return errItemNoConsumeUse;
	elseif dur - weapon.m_iteminfo.m_nCurDur > 1000 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "未修理的装备无法打孔。");
		return errItemNoConsumeUse;	
--	elseif yuanbao < 1000 then
--		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
--		return errItemNoConsumeUse;
	end
	local ret = bag:GenerateSocket(false,2);
	if ret == 1 then 
	--	bag:ChangeYuanbao(username,1000,false,91115,1);
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "打孔成功。");
	else
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "该装备打孔失败，物品和元宝不消耗。");
		return errItemNoConsumeUse;
	end
	return errSuccess;
end

function dakongshi_gaoji(pItem, pRole)    --高级打孔石
	local username = pRole:GetUserName();
		pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);	
	local bag = pRole:GetItemBag();

	local weapon = bag:GetItem(CONSLOT_DEFAULT, 0);
	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(weapon.m_iteminfo.m_nTemplateID);
	if weapon == nil or equip_data == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请将需要打孔的装备放在物品栏第一格再使用此物品.");
		return errItemNoConsumeUse;
	end

	local itemid = weapon.m_iteminfo.m_nTemplateID;
	local bind = weapon.m_iteminfo.m_byBindType;
	local dur = weapon.m_iteminfo.m_nMaxDur;
--	local yuanbao = pRole:GetItemBag():GetMoney(3);--元宝
	local socketcount = weapon.m_iteminfo.m_dwSocketCombination;

	if weapon.m_iteminfo.m_nSoulID[0] ~= 0 or  weapon.m_iteminfo.m_nSoulID[1] ~= 0 or  weapon.m_iteminfo.m_nSoulID[2] ~= 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请把宝石拆除后再使用此物品。");
		return errItemNoConsumeUse;
	end

	if socketcount < 10 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "必须拥有双孔才能进行高级打孔。");
		return errItemNoConsumeUse;
	end

	if bind == 10 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "绑定装备无法打孔。");
		return errItemNoConsumeUse;
	elseif dur - weapon.m_iteminfo.m_nCurDur > 1000 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "未修理的装备无法打孔。");
		return errItemNoConsumeUse;	
--	elseif yuanbao < 10000 then
--		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
--		return errItemNoConsumeUse;
	end

	local ret = bag:GenerateSocket(true,1);
	if ret == 1 then 
--		bag:ChangeYuanbao(username,10000,false,91225,1);
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "打孔成功。");
	else
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "该装备打孔失败，物品和元宝不消耗。");
		return errItemNoConsumeUse;
	end
	return errSuccess;
end

function zhuangbei_xilian2(pItem, pRole)    --装备洗炼2
	local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);	
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_DEFAULT, 0);
	local itemid = weapon.m_iteminfo.m_nTemplateID;
	if itemid == 99900031 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "洗练暂不支持逍遥扇。");
		return errItemNoConsumeUse;
	end

	if itemid == 999903261 or itemid == 999904261 or itemid == 999904361 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "只允许洗练最高级护手");
		return errItemNoConsumeUse;
	end
	local yuanbao = pRole:GetItemBag():GetMoney(3);--元宝
	local count1 = bag:GetItemCount(2800065, false);--沃玛精华
	
	if yuanbao < 1000 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
		return errItemNoConsumeUse;
	elseif count1 < 1  then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "祖玛精华不足。");
		return errItemNoConsumeUse;
	end
	--[[if itemid == 999904461 then
		local cls = pRole:GetClass();
		if weapon.m_iteminfo.m_wRandomAttrID[3] == 2001 or weapon.m_iteminfo.m_wRandomAttrID[3] == 4001 or weapon.m_iteminfo.m_wRandomAttrID[3] == 6001 then
			if cls == clsWarrior then
				weapon.m_iteminfo.m_wRandomAttrID[3] = 2001;
			elseif cls == clsMage then
				weapon.m_iteminfo.m_wRandomAttrID[3] = 4001;
			elseif cls == clsTaoist then
				weapon.m_iteminfo.m_wRandomAttrID[3] = 6001;
			end
		elseif weapon.m_iteminfo.m_wRandomAttrID[3] == 2011 or weapon.m_iteminfo.m_wRandomAttrID[3] == 4011 or weapon.m_iteminfo.m_wRandomAttrID[3] == 6011 then
			if cls == clsWarrior then
				weapon.m_iteminfo.m_wRandomAttrID[3] = 2011;
			elseif cls == clsMage then
				weapon.m_iteminfo.m_wRandomAttrID[3] = 4011;
			elseif cls == clsTaoist then
				weapon.m_iteminfo.m_wRandomAttrID[3] = 6011;
			end
		elseif weapon.m_iteminfo.m_wRandomAttrID[3] == 2021 or weapon.m_iteminfo.m_wRandomAttrID[3] == 4021 or weapon.m_iteminfo.m_wRandomAttrID[3] == 6021 then
			if cls == clsWarrior then
				weapon.m_iteminfo.m_wRandomAttrID[3] = 2021;
			elseif cls == clsMage then
				weapon.m_iteminfo.m_wRandomAttrID[3] = 4021;
			elseif cls == clsTaoist then
				weapon.m_iteminfo.m_wRandomAttrID[3] = 6021;
			end
		else
			pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "属性不正确，洗炼失败。");
			return errItemNoConsumeUse;
		end
		bag:ChangeYuanbao(username,1000,false,2800065,1);
		bag:DeleteItemId(2800065, 1, ITEMLOG_EQUIP_LEVELUP,false,0);
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "洗炼成功，请小退后刷新物品属性。");
		return errSuccess;
	end]]--
	local ret = bag:GenerateRandomAttributes1();
	if ret == 1 then
		bag:ChangeYuanbao(username,1000,false,2800065,1);
		bag:DeleteItemId(2800065, 1, ITEMLOG_EQUIP_LEVELUP,false,0);
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "洗炼成功。");
		return errSuccess;
	end;
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "只能洗练装备！");
	return errItemNoConsumeUse;
end


--充值礼包

function xinshou_zhulibao(pItem, pRole)
	local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local yuanbao = pRole:GetItemBag():GetMoney(3);
	if yuanbao < 600 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
		return errItemNoConsumeUse;
	end
	pRole:GetItemBag():ChangeYuanbao(username,600,false,3800001,1)
	pRole:GetItemBag():AddMoney(1, 100000, MONEYLOG_PACKAGE, 0,0);
	pRole:GetItemBag():AddItem(3800002, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(99920022, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetTitle():AddTitle(1);
	pRole:GetTitle():EquipTile(1);
	return errSuccess;
end

function tanshe_jiasubao(pItem, pRole)
	local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local yuanbao = pRole:GetItemBag():GetMoney(3);
	if yuanbao < 1800 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
		return errItemNoConsumeUse;
	end
	pRole:GetItemBag():ChangeYuanbao(username,1800,false,3800002,1)
	pRole:GetItemBag():AddItem(1800019, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(3800003, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(3800005, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(2800189, 1, ITEMLOG_REAL_MONEY_SHOP, 0, false);

	return errSuccess;
end

function qianghua_gongjubao(pItem, pRole)
	local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local yuanbao = pRole:GetItemBag():GetMoney(3);
	if yuanbao < 6800 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
		return errItemNoConsumeUse;
	end
	pRole:GetItemBag():ChangeYuanbao(username,6800,false,3800003,1)
	local cls = pRole:GetClass();
	if cls == clsWarrior then
		pRole:GetItemBag():AddItem(21001, 30, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	elseif cls == clsMage then
		pRole:GetItemBag():AddItem(21002, 30, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	elseif cls == clsTaoist then
		pRole:GetItemBag():AddItem(21003, 30, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	end
	pRole:GetItemBag():AddItem(2800064, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(3800004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(80003, 5, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(2800075, 2, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	return errSuccess;

end

function zunxiang_libao(pItem, pRole)
	local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local yuanbao = pRole:GetItemBag():GetMoney(3);
	if yuanbao < 18800 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
		return errItemNoConsumeUse;
	end
	pRole:GetItemBag():ChangeYuanbao(username,18800,false,3800004,1)
	pRole:GetItemBag():AddItem(2102, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(3800006, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(2212, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(2201, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	return errSuccess;
end

function shengjidan_35(pItem, pRole)--升级丹1
	local a = pRole:GetLevel()
	if a > 34 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "必须小于35级才能使用此物品");
		return errItemNoConsumeUse;
	end
	a = a + 1;
	pRole:SetLevel(a);
	return errSuccess;	
end

function jingyan_kabao(pItem, pRole)--经验卡包
	local index = math.random(8,12);
		pRole:GetItemBag():AddItem(2800044, index, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	return errSuccess;
end
function VIP_summonnpc(pItem, pRole)--VIP刷怪
	local map = pRole:GetSceneTempID()
	if map ~= 72 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请移步魔虫窟再使用此物品.");	
		return errItemNoConsumeUse;
	end
	local VIP = pRole:GetVIPLevel();
	if VIP == 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "只有尊贵的VIP才能使用此物品哦。");
		return errItemNoConsumeUse;
	end
	if VIP == 1 then
		local oNpc = pRole:GetScene():SpawnNpc(9746, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
		if oNpc == nil then
			return errItemNoConsumeUse;
		end
		return errSuccess;
	elseif VIP == 2 then
		local oNpc = pRole:GetScene():SpawnNpc(9747, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
		if oNpc == nil then
			return errItemNoConsumeUse;
		end
		return errSuccess;
	elseif VIP == 3 then
		local oNpc = pRole:GetScene():SpawnNpc(9748, pRole:GetX(), pRole:GetY(),pRole:GetZ() + GRID_WIDTH, pRole:GetFaceDirection(), 0, nil);
		if oNpc == nil then
			return errItemNoConsumeUse;
		end
		return errSuccess;
	end
	return errSuccess;
end

function PaoDian1(pItem, pRole)
local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local yuanbao = pRole:GetItemBag():GetMoney(3);
	if yuanbao < 3500 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
		return errItemNoConsumeUse;
	end
	pRole:GetItemBag():ChangeYuanbao(username,3500,false,2800139,1);
	pRole:GetTitle():AddTitle(30,2);
	return errSuccess;
end

function PaoDian2(pItem, pRole)
local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local yuanbao = pRole:GetItemBag():GetMoney(3);
	if yuanbao < 9000 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
		return errItemNoConsumeUse;
	end
	pRole:GetItemBag():ChangeYuanbao(username,9000,false,2800140,1);
	pRole:GetTitle():AddTitle(30,6);
	return errSuccess;
end

function PaoDian3(pItem, pRole)
local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local yuanbao = pRole:GetItemBag():GetMoney(3);
	if yuanbao < 16000 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
		return errItemNoConsumeUse;
	end
	pRole:GetItemBag():ChangeYuanbao(username,16000,false,2800141,1);
	pRole:GetTitle():AddTitle(30,12);
	return errSuccess;
end

function PaoDian4(pItem, pRole)
local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local yuanbao = pRole:GetItemBag():GetMoney(3);
	if yuanbao < 30000 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
		return errItemNoConsumeUse;
	end
	pRole:GetItemBag():ChangeYuanbao(username,30000,false,2800142,1);
	pRole:GetTitle():AddTitle(30,24);
	return errSuccess;
end

function YaoQing_LiBao(pItem, pRole)
	local username = pRole:GetUserName();
	pRole:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local yuanbao = pRole:GetItemBag():GetMoney(3);
	if yuanbao < 3800 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "元宝不足。");
		return errItemNoConsumeUse;
	end
	pRole:GetItemBag():ChangeYuanbao(username,3800,false,2800144,1);
	local cls = pRole:GetClass();
	if cls == clsWarrior then
	pRole:GetItemBag():AddItem(21001, 5, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(31034, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(2800145, 5, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	elseif cls == clsMage then
	pRole:GetItemBag():AddItem(21002, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(32546, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(2800146, 5, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	elseif cls == clsTaoist then
	pRole:GetItemBag():AddItem(21003, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(33012, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(2800147, 5, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	end	
	pRole:GetItemBag():AddItem(3800005, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	pRole:GetItemBag():AddItem(1800019, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	return errSuccess;
end

function huigui_mingwen(pItem, pRole)
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if (weapon == nil) then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴回归系列装备再使用此物品。");
		return errItemNoConsumeUse;
	end
	if weapon.m_iteminfo.m_nTemplateID == 199900018 then
		weapon.m_iteminfo.m_wRune[0] = 25414;
		weapon.m_iteminfo.m_wRune[1] = 25341;
		bag:Refreshitem(NES_MAIN_HAND,1);
		return errSuccess;
	end
	if weapon.m_iteminfo.m_nTemplateID == 199900019 then
		weapon.m_iteminfo.m_wRune[0] = 10313;
		weapon.m_iteminfo.m_wRune[1] = 10333;
		bag:Refreshitem(NES_MAIN_HAND,1);
		return errSuccess;
	end
	if weapon.m_iteminfo.m_nTemplateID == 199900021 then
		weapon.m_iteminfo.m_wRune[0] = 30043;
		weapon.m_iteminfo.m_wRune[1] = 30054;
		bag:Refreshitem(NES_MAIN_HAND,1);
		return errSuccess;
	end
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴回归系列装备再使用此物品。");
	return errItemNoConsumeUse;
end

function luandou_libao1(pItem, pRole)
	pRole:SetLevel(60);
	local bag = pRole:GetItemBag();
	local cls = pRole:GetClass();
	local sex = pRole:GetSex();
	if cls == clsWarrior then
		if sex == 1 then 
			pRole:GetItemBag():AddItem(599900018, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true); -- 上衣（男）
		else
			pRole:GetItemBag():AddItem(599900019, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);--上衣（女）
		end;
		pRole:GetItemBag():AddItem(599900001, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true); -- 并持短柄重型双手
		pRole:GetItemBag():AddItem(599900008, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900005, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900006, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900007, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900009, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900012, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900015, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900012, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900015, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(2800168, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(2800169, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:LearnSpell(1031, 3, true);
		pRole:LearnSpell(1032, 3, true);
		pRole:LearnSpell(1033, 3, true);
		pRole:LearnSpell(1034, 3, true);
		pRole:LearnSpell(1035, 3, true);
		pRole:LearnSpell(1036, 3, true);
		pRole:LearnSpell(1037, 3, true);
		pRole:LearnSpell(1038, 3, true);
		
		elseif cls == clsMage then
		if sex == 1 then 
			pRole:GetItemBag():AddItem(599900020, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true); -- 上衣（男）
		else
			pRole:GetItemBag():AddItem(599900021, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);--上衣（女）
		end;
		pRole:GetItemBag():AddItem(599900003, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true); -- 并持短柄重型双手
		pRole:GetItemBag():AddItem(599900008, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900005, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900006, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900007, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900010, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900013, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900016, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900013, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900016, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(2800168, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(2800169, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		--[[pRole:LearnSpell(2531, 3, true);
		pRole:LearnSpell(2532, 3, true);
		pRole:LearnSpell(2533, 3, true);
		pRole:LearnSpell(2534, 3, true);
		pRole:LearnSpell(2535, 3, true);
		pRole:LearnSpell(2536, 3, true);
		pRole:LearnSpell(2537, 3, true);
		pRole:LearnSpell(2538, 3, true);
		pRole:LearnSpell(2539, 3, true);
		pRole:LearnSpell(2540, 3, true);
		pRole:LearnSpell(2541, 3, true);
		pRole:LearnSpell(2544, 3, true);
		pRole:LearnSpell(2545, 3, true);
		pRole:LearnSpell(2546, 3, true);
		pRole:LearnSpell(2549, 3, true);
		pRole:LearnSpell(2550, 3, true);]]--
		
	elseif cls == clsTaoist then
		if sex == 1 then 
			pRole:GetItemBag():AddItem(599900022, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true); -- 上衣（男）
		else
			pRole:GetItemBag():AddItem(599900023, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);--上衣（女）
		end;
		pRole:GetItemBag():AddItem(599900002, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true); -- 并持短柄重型双手
		pRole:GetItemBag():AddItem(599900008, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900005, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900006, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900007, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900011, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900014, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900017, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900014, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(599900017, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(2800168, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(2800169, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40103, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40014, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40103, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40014, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40103, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40014, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40103, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40014, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40103, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40014, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40103, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40014, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40103, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40014, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40103, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40004, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(40014, 1, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		pRole:GetItemBag():AddItem(1800040, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
		--[[pRole:LearnSpell(3001, 3, true);
		pRole:LearnSpell(3002, 3, true);
		pRole:LearnSpell(3003, 3, true);
		pRole:LearnSpell(3004, 3, true);
		pRole:LearnSpell(3005, 3, true);
		pRole:LearnSpell(3006, 3, true);
		pRole:LearnSpell(3007, 3, true);
		pRole:LearnSpell(3008, 3, true);
		pRole:LearnSpell(3009, 3, true);
		pRole:LearnSpell(3010, 3, true);
		pRole:LearnSpell(3011, 3, true);
		pRole:LearnSpell(3012, 3, true);
		pRole:LearnSpell(3014, 3, true);
		pRole:LearnSpell(3015, 3, true);
		pRole:LearnSpell(3018, 3, true);]]--

	end;
	return errSuccess;
		
end

function wuxian_qianghua(pItem,pRole)
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	if (weapon == nil) then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴乱斗系列武器再使用此物品。");
		return errItemNoConsumeUse;
	end
	if weapon.m_iteminfo.m_nTemplateID == 599900001 then
		weapon.m_iteminfo.m_wRune[0] = 10353;
		weapon.m_iteminfo.m_wRune[1] = 10361;
		weapon.m_iteminfo.m_byLuck = 7;
		bag:WeaponLevelUp1(7);
	return errSuccess;
	end

	if weapon.m_iteminfo.m_nTemplateID == 599900002 then
		weapon.m_iteminfo.m_wRune[0] = 30043;
		weapon.m_iteminfo.m_wRune[1] = 30083;
		weapon.m_iteminfo.m_byLuck = 7;
		bag:WeaponLevelUp1(7);
	return errSuccess;
	end
	if weapon.m_iteminfo.m_nTemplateID == 599900003 then
		weapon.m_iteminfo.m_wRune[0] = 25363;
		weapon.m_iteminfo.m_wRune[1] = 25352;
		weapon.m_iteminfo.m_byLuck = 7;
		bag:WeaponLevelUp1(7);
	return errSuccess;
	end
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴乱斗系列武器再使用此物品。");
	return errItemNoConsumeUse;
end


function liaoshangyao_3(pItem,pRole)
	pRole:ChangeHp(150,cdrRecovery);
	pRole:ChangeMp(300);
	pRole:GetItemBag():AddItem(2800169, 1, ITEMLOG_REAL_MONEY_SHOP, 0, false);
	return errSuccess;
end

function jingyan_ka1(pItem, pRole)--50W经验卡
	pRole:AddExp(500000, false,false);
	return errSuccess;
end	

function jinbi_ka50(pItem, pRole)--50W金币卡
	pRole:GetItemBag():AddMoney(1, 500000, MONEYLOG_PACKAGE, 0,0);
	return errSuccess;
end	

function feixing(pItem, pRole)--飞星
	local username = pRole:GetUserName();
	--第一个骰子
	local  first = math.random(6);
	--第二个骰子
	local  second = math.random(6);
	--第三个骰子
	local  third = math.random(6);
	
	local sum = first * 100 + second * 10 + third;
	pRole:SetVariable(1010,sum);
	
	if first == second and second == third then
		pRole:GetItemBag():ChangeYuanbao(username,1000,true,2800224,1000);--豹子的返利
		local msg = first.." "..second.." "..third.."，三位一体，恭喜您获得1000元宝！";
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, msg);
		local message = "恭喜玩家"..pRole:GetName().."喜中三位一体，获得大量元宝！";
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, msg);
		pRole:Say(cctGroup, cltTvShow, message);
	elseif sum == 123 or sum == 132 or sum == 213 or sum == 231 or sum == 312 or sum == 321 or sum == 456 or sum == 465 or sum == 546 or sum == 564 or sum == 645 or sum == 654 then
		pRole:GetItemBag():ChangeYuanbao(username,400,true,2800224,400);--顺子的返利	 
		local msg = first.." "..second.." "..third.."，三星连珠，恭喜您获得400元宝！";
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, msg);
	elseif first == second or first == third or second == third then
		pRole:GetItemBag():ChangeYuanbao(username,110,true,2800224,110);--对子的返利	 
		local msg = first.." "..second.." "..third.."，双星吉祥，恭喜您获得110元宝！";
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, msg);
	else
		local msg = first.." "..second.." "..third.."，飞星落地，再接再厉！";
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, msg);
	end
	return errSuccess;
end

function chongji1_libao(pItem, pRole)
 local a = os.time();
 local b = pRole:GetVariable(1006);
 local level = pRole:GetLevel();
 local username = pRole:GetUserName();
	if b == nil then
		return errItemNoConsumeUse;
	elseif level < 40 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "等级不足，无法使用。");	
		return errItemNoConsumeUse;
	elseif b + 266400 >= a then 
		pRole:GetItemBag():ChangeYuanbao(username,5000,true,2800273,1);
	elseif b + 439200 >= a then 
		pRole:GetItemBag():ChangeYuanbao(username,2500,true,2800273,1);
	end
	pRole:GetItemBag():AddItem(1800019, 1, ITEMLOG_SCRIPT, 0, true); -- 500W双倍经验丹
	pRole:GetItemBag():AddItem(1800040, 2, ITEMLOG_SCRIPT, 0, true); --特修券
	pRole:GetItemBag():AddItem(2800277, 5, ITEMLOG_SCRIPT, 0, true); --聚宝盆
	pRole:GetItemBag():AddItem(2800190, 1, ITEMLOG_SCRIPT, 0, true); --聚灵匣(中)
	
	return errSuccess;	
end

function chongji2_libao(pItem, pRole)
 local a = os.time();
 local b = pRole:GetVariable(1006);
 local level = pRole:GetLevel();
 local username = pRole:GetUserName();
	if b == nil then
		return errItemNoConsumeUse;
	elseif level < 43 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "等级不足，无法使用。");	
		return errItemNoConsumeUse;
	elseif b + 439200 >= a then 
		pRole:GetItemBag():ChangeYuanbao(username,10000,true,2800274,1);
	elseif b + 612000 >= a then 
		pRole:GetItemBag():ChangeYuanbao(username,5000,true,2800274,1);
	end
	pRole:GetItemBag():AddItem(1800018, 1, ITEMLOG_SCRIPT, 0, true); -- 10%双倍经验丹
	pRole:GetItemBag():AddItem(1800040, 2, ITEMLOG_SCRIPT, 0, true); --特修券
	pRole:GetItemBag():AddItem(80003, 10, ITEMLOG_SCRIPT, 0, true); -- 祝福油
	local cls = pRole:GetClass();
	if cls == clsWarrior then
		pRole:GetItemBag():AddItem(21001, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	elseif cls == clsMage then
		pRole:GetItemBag():AddItem(21002, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	elseif cls == clsTaoist then
		pRole:GetItemBag():AddItem(21003, 10, ITEMLOG_REAL_MONEY_SHOP, 0, true);
	end
	pRole:GetItemBag():AddItem(2800064, 1, ITEMLOG_SCRIPT, 0, true); --魔龙血

	return errSuccess;	
end


function yueka1_libao(pItem, pRole)
	local yue1 = pRole:GetTitle():FindTitle(91);
	local yue2 = pRole:GetTitle():FindTitle(92);
	if yue1 == true or yue2 == true then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "您已拥有月卡，无法再开启礼包。");	
		return errItemNoConsumeUse;
	else
		pRole:GetItemBag():AddItem(2800075, 10, ITEMLOG_SCRIPT, 0, true); --沃玛精华
		pRole:GetItemBag():AddItem(2800044, 20, ITEMLOG_SCRIPT, 0, true);--经验卡
		pRole:GetItemBag():AddMoney(1, 100000, MONEYLOG_PACKAGE, 0,0); --金币
		pRole:GetTitle():AddTitle(91);
		pRole:GetScene():Say(pRole:GetObjID(), cltLighting, "恭喜您成打开88元月卡礼包，你拥有以下特权：金币交易税降低至5%，土城商店通用卖货，土城商店购买物品9.5折，签到奖励*2， 药品体力恢复加成10%");
		return errSuccess;
	end
end

function yueka2_libao(pItem, pRole)
	local yue1 = pRole:GetTitle():FindTitle(91);
	local yue2 = pRole:GetTitle():FindTitle(92);
	if yue1 == true or yue2 == true then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "您已拥有月卡，无法再开启礼包。");	
		return errItemNoConsumeUse;
	else
		pRole:GetItemBag():AddItem(2800075, 30, ITEMLOG_SCRIPT, 0, true); --沃玛精华
		pRole:GetItemBag():AddItem(2800044, 50, ITEMLOG_SCRIPT, 0, true);--经验卡
		pRole:GetItemBag():AddMoney(1, 500000, MONEYLOG_PACKAGE, 0,0); --金币
		pRole:GetTitle():AddTitle(92);
		pRole:GetScene():Say(pRole:GetObjID(), cltLighting, "恭喜您成打开188元月卡礼包，你拥有以下特权：金币交易税降低至3%，土城商店通用卖货，土城商店购买物品8.5折，签到奖励*2，药品体力恢复加成10%，攻速+1， 经验加成3%");
		return errSuccess;
	end
end

function gupiao(pItem, pRole)
	local username = pRole:GetUserName();
	local level = pRole:GetLevel();
	if level < 35 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "30级以下使用是获取不到返利的哦。");	
		return errItemNoConsumeUse;
	elseif level == 35 then
		pRole:GetItemBag():ChangeYuanbao(username,10000,true,2800283,1);
	elseif level == 36 then
		pRole:GetItemBag():ChangeYuanbao(username,10200,true,2800283,1);
	elseif level == 37 then
		pRole:GetItemBag():ChangeYuanbao(username,10400,true,2800283,1);
	elseif level == 38 then
		pRole:GetItemBag():ChangeYuanbao(username,10600,true,2800283,1);
	elseif level == 39 then
		pRole:GetItemBag():ChangeYuanbao(username,10800,true,2800283,1);
	elseif level == 40 then
		pRole:GetItemBag():ChangeYuanbao(username,11000,true,2800283,1);
	elseif level == 41 then
		pRole:GetItemBag():ChangeYuanbao(username,11300,true,2800283,1);
	elseif level == 42 then
		pRole:GetItemBag():ChangeYuanbao(username,11600,true,2800283,1);
	elseif level == 43 then
		pRole:GetItemBag():ChangeYuanbao(username,12000,true,2800283,1);
	elseif level == 44 then
		pRole:GetItemBag():ChangeYuanbao(username,12500,true,2800283,1);
	elseif level == 45 then
		pRole:GetItemBag():ChangeYuanbao(username,13000,true,2800283,1);
	elseif level == 46 then
		pRole:GetItemBag():ChangeYuanbao(username,13500,true,2800283,1);
	elseif level == 47 then
		pRole:GetItemBag():ChangeYuanbao(username,14000,true,2800283,1);
	elseif level == 48 then
		pRole:GetItemBag():ChangeYuanbao(username,14500,true,2800283,1);
	elseif level == 49 then
		pRole:GetItemBag():ChangeYuanbao(username,15000,true,2800283,1);
	elseif level == 50 then
		pRole:GetItemBag():ChangeYuanbao(username,16000,true,2800283,1);
	elseif level == 51 then
		pRole:GetItemBag():ChangeYuanbao(username,16500,true,2800283,1);
	elseif level == 52 then
		pRole:GetItemBag():ChangeYuanbao(username,17000,true,2800283,1);
	elseif level == 53 then
		pRole:GetItemBag():ChangeYuanbao(username,18000,true,2800283,1);
	elseif level == 54 then
		pRole:GetItemBag():ChangeYuanbao(username,19000,true,2800283,1);
	elseif level == 55 then
		pRole:GetItemBag():ChangeYuanbao(username,20000,true,2800283,1);
	elseif level == 56 then
		pRole:GetItemBag():ChangeYuanbao(username,21000,true,2800283,1);
	elseif level == 57 then
		pRole:GetItemBag():ChangeYuanbao(username,22000,true,2800283,1);
	elseif level == 58 then
		pRole:GetItemBag():ChangeYuanbao(username,23000,true,2800283,1);
	elseif level == 59 then
		pRole:GetItemBag():ChangeYuanbao(username,24000,true,2800283,1);
	else
		pRole:GetItemBag():ChangeYuanbao(username,25000,true,2800283,1);
	end
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "你已领取股票中的返利，谢谢您的参与。");	
	return errSuccess;
end

function baoxiang_tulong(pItem, pRole)--屠龙宝箱
	local index = math.random(20,30);
		pRole:GetItemBag():AddItem(2800285, index, ITEMLOG_REAL_MONEY_SHOP, 0, false);
	return errSuccess;
end

function juanbang(pItem, pRole)--捐榜
	local new_count = pRole:GetVariable(194) + 1;
	pRole:SetVariable(194, new_count);
	--pRole:SetVariable(1003, os.time());
	pRole:UpdateRankListNode(rlActivity01, 0, new_count);
	local msg = "您总共捐献 "..new_count .. " 个英雄帖！";
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, msg);
	return errSuccess;
end

function baoshi_hecheng(pItem, pRole)
	local baoshi_one = pRole:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local baoshi_two = pRole:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	local rea = false;
	if baoshi_one == nil or baoshi_two ==nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够合成的宝石。");
		return errItemNoConsumeUse;
	end
	local itemid_one = baoshi_one.m_iteminfo.m_nTemplateID;
	local itemid_two = baoshi_two.m_iteminfo.m_nTemplateID; 
	local dengji_one = itemid_one % 10;
	local dengji_two = itemid_two % 10;
	
	for i = 0,5 do --宝石是否能够合成判定
		if itemid_one == g_GWConfig.nBaoShi_PuTong[i] and itemid_two == g_GWConfig.nBaoShi_PuTong[i] then
			rea = true;
			break;
		else
			rea = false;
		end	
	end
	
	
	if itemid_one ~= itemid_two or itemid_one > 11100 or itemid_one < 10110 or itemid_two > 11100 or itemid_two < 10110 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请在背包第一格与第二格相同的宝石。");
		return errItemNoConsumeUse;
		
	elseif dengji_one ~= 0 or dengji_two ~= 0 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请在背包第一格与第二格放入相同的一级宝石。");
		return errItemNoConsumeUse;
	elseif rea == false then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "此类宝石无法进行合成。");
		return errItemNoConsumeUse;
		
	end
	
	local index = math.random(1,5);
	
	if index <= 2 then
		pRole:GetItemBag():DeleteItemPos(CONSLOT_DEFAULT, 0, 1, MONEYLOG_SHENGXING, 0);
		pRole:GetItemBag():DeleteItemPos(CONSLOT_DEFAULT, 1, 1, MONEYLOG_SHENGXING, 0);	
		pRole:GetItemBag():AddItem(itemid_one+1, 1, ITEMLOG_SCRIPT, 0, true);--宝石合成
		local msg = "合成成功，恭喜获得"..pRole:GetItemBag():GetItemName(itemid_one + 1).."!"
			pRole:Say(pRole:GetObjID(), cltTvShow, msg);
		return errSuccess;
	else
		pRole:GetItemBag():DeleteItemPos(CONSLOT_DEFAULT, 1, 1, MONEYLOG_SHENGXING, 0);	
		local msg = "合成失败，返还"..pRole:GetItemBag():GetItemName(itemid_one).."!"
			pRole:Say(pRole:GetObjID(), cltTvShow, msg);
		return errSuccess;
	end	

end
function baoshi_hecheng_1(pItem, pRole)
	local baoshi_one = pRole:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local rea = false;
	if baoshi_one == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请在背包第一格放入能够合成的宝石。");
		return errItemNoConsumeUse;
	end
	local itemid_one = baoshi_one.m_iteminfo.m_nTemplateID;
	local dengji_one = itemid_one % 10;
	
	for i = 0,27 do --宝石是否能够合成判定
		if itemid_one == g_GWConfig.nBaoShi_HeCheng[i] then
			rea = true;
			break;
		else
			rea = false;
		end	
	end
	

	local count = pRole:GetItemBag():GetItemCount(itemid_one, false);--宝石
	local count1 = pRole:GetItemBag():GetItemCount(2800372, false);--保底券
	if rea == false then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请在背包第一格放入能够合成宝石。");
		return errItemNoConsumeUse;
	elseif count < 100 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "宝石数量不足。");
		return errItemNoConsumeUse;
	end
	
	
	local index = math.random(1,5);
	
	if index <= 2 then			
		pRole:GetItemBag():DeleteItemId(itemid_one, 100, MONEYLOG_SHENGXING,false,0);
		pRole:GetItemBag():AddItem(itemid_one+1, 1, ITEMLOG_SCRIPT, 0, true);--宝石合成
		local msg = "合成成功，恭喜获得"..pRole:GetItemBag():GetItemName(itemid_one + 1).."!"
			pRole:Say(pRole:GetObjID(), cltTvShow, msg);
		return errSuccess;
	elseif count1 > 0 then
		pRole:GetItemBag():DeleteItemId(2800372, 1, MONEYLOG_SHENGXING,false,0);
		local msg = "合成失败，返还"..pRole:GetItemBag():GetItemName(itemid_one).."*100!"
			pRole:Say(pRole:GetObjID(), cltTvShow, msg);
		return errSuccess;
	else		
		pRole:GetItemBag():DeleteItemId(itemid_one, 100, MONEYLOG_SHENGXING,false,0);
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "合成失败，宝石消失。");
		return errSuccess;
	end	

end

function tianshan_xuelian(pItem, pRole)
	pRole:GetTitle():AddTitle(9);
end

function OnUseVip1Day(pItem, pRole)
	pRole:GetScene():Say(pRole:GetObjID(), cltLighting, "恭喜您成为白银会员，你拥有以下特权：聚灵珠60%效率，每日食用上限：6个，召唤物存活时间+1小时，宠物下线保护5分钟，商店折扣-1%，个人爆率+5%，额外经验获取+5%，魔虫窟次数+1。");
   	return pRole:SubscribeVIP(1,1);
end

function zhanyue_jibu(pItem, pRole)
	local bag = pRole:GetItemBag();
	local weapon = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
--	local zhuangbei = pRole:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	if weapon == nil  then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴武器再使用此物品。");
		return errItemNoConsumeUse;
	end
	weapon.m_iteminfo.m_wRune[0] = 10361;
	weapon.m_iteminfo.m_wRune[1] = 10353;
	bag:Refreshitem(NES_MAIN_HAND);
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "武器铭文洗炼成功。");
	return errSuccess;
end 

function wuqi_zhuanyi(pItem, pRole)
	local bag = pRole:GetItemBag();
	local zhuangbei = bag:GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
	local weapon = pRole:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local id = zhuangbei.m_iteminfo.m_nTemplateID;
	local luck = weapon.m_iteminfo.m_byLuck;
	local gongji = weapon.m_iteminfo.m_byLevelupPhyPoint;
	local mofa = weapon.m_iteminfo.m_byLevelupMagPoint;
	local daoshu = weapon.m_iteminfo.m_byLevelupTaoPoint;
	local mingwen1 = weapon.m_iteminfo.m_wRune[0];
	local mingwen2 = weapon.m_iteminfo.m_wRune[1];
	

	if zhuangbei == nil  then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请佩戴没有铭文、幸运、强化属性的武器再使用此物品。");
		return errItemNoConsumeUse;
	end	
	if weapon == nil then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请在背包第一格放入被转移的武器再使用此物品。");
		return errItemNoConsumeUse;
	end
	local Type = weapon.m_pTemplate.m_bySubType;
	
	if Type ~= 1 then
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "请在背包第一格放入被转移的武器再使用此物品。");
		return errItemNoConsumeUse;
	end	
	bag:DeleteItemPos(CONSLOT_EQUIPPED, NES_MAIN_HAND, 1, 2800364, 0);
	bag:DeleteItemPos(CONSLOT_DEFAULT, 0, 1, MONEYLOG_SHENGXING, 0);
	bag:AddItem1(id,1,MONEYLOG_SHENGXING,0,false,weapon);
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "武器属性转移成功。");
	return errSuccess;

end 

function OnUseVip188(pItem, pRole)
	local VIP = pRole:GetVIPLevel();
	local username = pRole:GetUserName();
	local cDateCurrectTime = os.date("*t",os.time());
	local cDateTodayTime = os.time({year=cDateCurrectTime.year, month=cDateCurrectTime.month, day=cDateCurrectTime.day, hour=0,min=0,sec=0});
	--[[if VIP == 1 then
		local expirytime = pRole:GetVIPTime(1);
		local days = (expirytime - cDateTodayTime) / 86400;
		pRole:GetItemBag():ChangeYuanbao(username,days * 200,true,2103,1);
	end
	if VIP == 2 then
		local expirytime = pRole:GetVIPTime(2);
		local days = (expirytime - cDateTodayTime) / 86400;
		pRole:GetItemBag():ChangeYuanbao(username,days * 900,true,2103,1);
	end]]--
	pRole:GetScene():Say(pRole:GetObjID(), cltLighting, "恭喜您成为钻石会员，你拥有以下特权：召唤物存活时间+2小时，宠物下线保护60分钟，商店折扣-5%，个人爆率+15%，个额外经验获取+10%，魔虫窟次数+3。");
    return pRole:SubscribeVIP(3,31);
end

function libao_chongji(pItem, pRole)
	local a = os.time();
	local b = pRole:GetVariable(1006);
	local level = pRole:GetLevel();
	local username = pRole:GetUserName();
	
	if b == nil then
		return errItemNoConsumeUse;
	elseif level < 40 then 
		pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "等级不足，无法使用。");	
		return errItemNoConsumeUse;
	
	elseif b + 1296000 >= a then   
		pRole:GetItemBag():ChangeYuanbao(username,30000,true,2800368,1);
	elseif b + 1728000 >= a then 
		pRole:GetItemBag():ChangeYuanbao(username,20000,true,2800368,1);
	end	
	return errSuccess;	
end



---------- 自己新增代码 begin

-- 点卡5小时 (1小时 == 3600秒)
function OnAddTimeCard_5Hours(pItem, pRole)
    pRole:AddGameTimeCard(5 * 3600);
	return errSuccess;
end

-- 点卡12小时
function OnAddTimeCard_12Hours(pItem, pRole)
    pRole:AddGameTimeCard(12 * 3600);
	return errSuccess;
end

-- 点卡24小时
function OnAddTimeCard_24Hours(pItem, pRole)
    pRole:AddGameTimeCard(24 * 3600);
	return errSuccess;
end

-- 点卡48小时
function OnAddTimeCard_48Hours(pItem, pRole)
    pRole:AddGameTimeCard(48 * 3600);
	return errSuccess;
end

-- 点卡72小时
function OnAddTimeCard_72Hours(pItem, pRole)
    pRole:AddGameTimeCard(72 * 3600);
	return errSuccess;
end

-- 测试铭文
function OnRuneTest(pItem, pRole)
	-- pRole:GetItemBag():RuneTest(0);  -- 清空铭文
	
	-- pRole:GetItemBag():RuneTest(25363);  -- 疾光电影-雷咒印
	
	-- pRole:GetItemBag():RuneTest(30031);  -- 召唤骷髅-君王印
	-- pRole:GetItemBag():RuneTest(30032);  -- 召唤骷髅-迦兰印
	-- pRole:GetItemBag():RuneTest(30033);  -- 召唤骷髅-偷天印
	
	-- pRole:GetItemBag():RuneTest(30081);  -- 召唤神兽-圣兽印
	-- pRole:GetItemBag():RuneTest(30082);  -- 召唤神兽-血兽印
	-- pRole:GetItemBag():RuneTest(30083);  -- 召唤神兽-灵兽印
	
	-- pRole:GetItemBag():RuneTest(25411);  -- 诱惑之光-军势印 诱惑数量+1
	-- pRole:GetItemBag():RuneTest(25412);  -- 诱惑之光-魔语印 延长叛变时间
	-- pRole:GetItemBag():RuneTest(25413);  -- 诱惑之光-魔魇印 提高诱惑成功率
	-- pRole:GetItemBag():RuneTest(25414);  -- 诱惑之光-血契印 怪物初始等级与技能等级相同
	-- pRole:GetItemBag():RuneTest(25415);  -- 诱惑之光-噬魂印 祖玛雕像
	-- pRole:GetItemBag():RuneTest(25416);  -- 诱惑之光-邪光印 红野猪
	-- pRole:GetItemBag():RuneTest(25417);  -- 诱惑之光-邪影印 沃玛勇士

	return 0;
end

-- 战士技能书, 8个
function OnAddBook_ZhanShi(pItem, pRole)
	pRole:GetItemBag():AddItem(31031, 1, ITEMLOG_SCRIPT, 0, false);  -- 基本剑术
	pRole:GetItemBag():AddItem(31032, 1, ITEMLOG_SCRIPT, 0, false);  -- 攻杀剑术
	pRole:GetItemBag():AddItem(31033, 1, ITEMLOG_SCRIPT, 0, false);  -- 刺杀剑术
	pRole:GetItemBag():AddItem(31034, 1, ITEMLOG_SCRIPT, 0, false);  -- 半月弯刀
	pRole:GetItemBag():AddItem(31035, 1, ITEMLOG_SCRIPT, 0, false);  -- 野蛮冲撞
	pRole:GetItemBag():AddItem(31036, 1, ITEMLOG_SCRIPT, 0, false);  -- 烈火剑法
	pRole:GetItemBag():AddItem(31037, 1, ITEMLOG_SCRIPT, 0, false);  -- 狮子吼
	pRole:GetItemBag():AddItem(31038, 1, ITEMLOG_SCRIPT, 0, false);  -- 逐日剑法
	return errSuccess;
end

-- 法师技能书, 17个
function OnAddBook_FaShi(pItem, pRole)
	pRole:GetItemBag():AddItem(32531, 1, ITEMLOG_SCRIPT, 0, false);  -- 火球术
	pRole:GetItemBag():AddItem(32532, 1, ITEMLOG_SCRIPT, 0, false);  -- 抗拒火环
	pRole:GetItemBag():AddItem(32541, 1, ITEMLOG_SCRIPT, 0, false);  -- 诱惑之光
	pRole:GetItemBag():AddItem(32544, 1, ITEMLOG_SCRIPT, 0, false);  -- 地狱火
	pRole:GetItemBag():AddItem(32533, 1, ITEMLOG_SCRIPT, 0, false);  -- 雷电术
	pRole:GetItemBag():AddItem(32538, 1, ITEMLOG_SCRIPT, 0, false);  -- 瞬息移动
	pRole:GetItemBag():AddItem(32545, 1, ITEMLOG_SCRIPT, 0, false);  -- 爆裂火焰
	pRole:GetItemBag():AddItem(32534, 1, ITEMLOG_SCRIPT, 0, false);  -- 火墙
	pRole:GetItemBag():AddItem(32536, 1, ITEMLOG_SCRIPT, 0, false);  -- 疾光电影
	pRole:GetItemBag():AddItem(32546, 1, ITEMLOG_SCRIPT, 0, false);  -- 地狱雷光
	pRole:GetItemBag():AddItem(32535, 1, ITEMLOG_SCRIPT, 0, false);  -- 魔法盾
	pRole:GetItemBag():AddItem(32547, 1, ITEMLOG_SCRIPT, 0, false);  -- 圣言术
	pRole:GetItemBag():AddItem(32537, 1, ITEMLOG_SCRIPT, 0, false);  -- 冰咆哮
	pRole:GetItemBag():AddItem(32550, 1, ITEMLOG_SCRIPT, 0, false);  -- 寒冰掌
	pRole:GetItemBag():AddItem(32549, 1, ITEMLOG_SCRIPT, 0, false);  -- 大火球
	pRole:GetItemBag():AddItem(32539, 1, ITEMLOG_SCRIPT, 0, false);  -- 灭天火
	pRole:GetItemBag():AddItem(32540, 1, ITEMLOG_SCRIPT, 0, false);  -- 流星火雨
	return errSuccess;
end

-- 道士技能书, 15个
function OnAddBook_DaoShi(pItem, pRole)
	pRole:GetItemBag():AddItem(33002, 1, ITEMLOG_SCRIPT, 0, false);  -- 治愈术
	pRole:GetItemBag():AddItem(33001, 1, ITEMLOG_SCRIPT, 0, false);  -- 精神力战法
	pRole:GetItemBag():AddItem(33004, 1, ITEMLOG_SCRIPT, 0, false);  -- 施毒术
	pRole:GetItemBag():AddItem(33005, 1, ITEMLOG_SCRIPT, 0, false);  -- 灵魂火符
	pRole:GetItemBag():AddItem(33003, 1, ITEMLOG_SCRIPT, 0, false);  -- 召唤骷髅
	pRole:GetItemBag():AddItem(33009, 1, ITEMLOG_SCRIPT, 0, false);  -- 隐身术
	pRole:GetItemBag():AddItem(33014, 1, ITEMLOG_SCRIPT, 0, false);  -- 集体隐身术
	pRole:GetItemBag():AddItem(33006, 1, ITEMLOG_SCRIPT, 0, false);  -- 幽灵盾
	pRole:GetItemBag():AddItem(33007, 1, ITEMLOG_SCRIPT, 0, false);  -- 神圣战甲术
	pRole:GetItemBag():AddItem(33011, 1, ITEMLOG_SCRIPT, 0, false);  -- 困魔咒
	pRole:GetItemBag():AddItem(33018, 1, ITEMLOG_SCRIPT, 0, false);  -- 气功波
	pRole:GetItemBag():AddItem(33012, 1, ITEMLOG_SCRIPT, 0, false);  -- 群体治愈术
	pRole:GetItemBag():AddItem(33008, 1, ITEMLOG_SCRIPT, 0, false);  -- 召唤神兽
	pRole:GetItemBag():AddItem(33015, 1, ITEMLOG_SCRIPT, 0, false);  -- 无极真气
	pRole:GetItemBag():AddItem(33010, 1, ITEMLOG_SCRIPT, 0, false);  -- 噬血术
	return errSuccess;
end

-- 2000011-黑铁矿石盲盒(普通)
function BlackIron_Normal(pItem, pRole)
	local arr_items = 
	{
		{ item_id = 114003, item_count = 1, weight = 1000 },
		{ item_id = 114004, item_count = 1, weight = 1000 },
		{ item_id = 114005, item_count = 1, weight = 1000 },
		{ item_id = 114006, item_count = 1, weight = 1000 },
		{ item_id = 114007, item_count = 1, weight = 1000 },
		{ item_id = 114008, item_count = 1, weight = 1000 },
		{ item_id = 114009, item_count = 1, weight = 1000 },
		{ item_id = 114010, item_count = 1, weight = 1000 },
		{ item_id = 114011, item_count = 1, weight = 1000 },
		{ item_id = 114012, item_count = 1, weight = 1000 },
		{ item_id = 114013, item_count = 1, weight = 1000 },
		{ item_id = 114014, item_count = 1, weight = 1000 },
		{ item_id = 114015, item_count = 1, weight = 1000 },
		{ item_id = 114016, item_count = 1, weight = 1000 },
		{ item_id = 114017, item_count = 1, weight = 1000 },
		{ item_id = 114018, item_count = 1, weight = 1000 },
		{ item_id = 114019, item_count = 1, weight = 1000 },
		{ item_id = 114020, item_count = 1, weight = 1000 },
		{ item_id = 114021, item_count = 1, weight = 1000 },
		{ item_id = 114022, item_count = 1, weight = 1000 },
		{ item_id = 114023, item_count = 1, weight = 1000 },
		{ item_id = 114024, item_count = 1, weight = 1000 },
		{ item_id = 114025, item_count = 1, weight = 1000 },
		{ item_id = 114026, item_count = 1, weight = 1000 },
	};
	
	-- 计算总权重
	local totalweight = 0;
	for index,item in ipairs(arr_items) do
		if item.item_id and item.item_count and item.weight and item.weight > 0 then
			totalweight = totalweight + item.weight;
		else
			print("BlackIron_Normal is worng in totalweight");
			return 0;
		end
	end
	-- print("totalweight: ".. totalweight);
	
	-- 随机数
	local random_number = math.random(totalweight);
	
    -- 使用累计权重方法选择物品
    local accumulated_weight = 0
    local selected_item = nil
	
	-- 随机
    for _, item in ipairs(arr_items) do
        accumulated_weight = accumulated_weight + item.weight
        if random_number <= accumulated_weight then
            selected_item = item
            break
        end
    end
	
    -- 添加物品
    if selected_item then
        pRole:GetItemBag():AddItem(selected_item.item_id, selected_item.item_count, ITEMLOG_PACKAGE, selected_item.item_id, false);
        -- print(string.format("选中物品: ID=%d, 数量=%d", selected_item.item_id, selected_item.item_count));
    end
	
	return errSuccess;
end

-- 2000012-黑铁矿石盲盒(高级)
function BlackIron_Advance(pItem, pRole)
	local bao_di_open = true;        -- 保底开关
	local bao_di_counts = 10;        -- 保底次数
	local bao_di_item_id = 114025;   -- 保底物品ID
	local bao_di_item_count = 1;     -- 保底物品数量
	local bao_di_checkvariable = 1800;  -- 判断变量
	
	local arr_items = 
	{
		{ item_id = 114003, item_count = 1, weight = 1000 },
		{ item_id = 114004, item_count = 1, weight = 1000 },
		{ item_id = 114005, item_count = 1, weight = 1000 },
		{ item_id = 114006, item_count = 1, weight = 1000 },
		{ item_id = 114007, item_count = 1, weight = 1000 },
		{ item_id = 114008, item_count = 1, weight = 1000 },
		{ item_id = 114009, item_count = 1, weight = 1000 },
		{ item_id = 114010, item_count = 1, weight = 1000 },
		{ item_id = 114011, item_count = 1, weight = 1000 },
		{ item_id = 114012, item_count = 1, weight = 1000 },
		{ item_id = 114013, item_count = 1, weight = 1000 },
		{ item_id = 114014, item_count = 1, weight = 1000 },
		{ item_id = 114015, item_count = 1, weight = 1000 },
		{ item_id = 114016, item_count = 1, weight = 1000 },
		{ item_id = 114017, item_count = 1, weight = 1000 },
		{ item_id = 114018, item_count = 1, weight = 1000 },
		{ item_id = 114019, item_count = 1, weight = 1000 },
		{ item_id = 114020, item_count = 1, weight = 1000 },
		{ item_id = 114021, item_count = 1, weight = 1000 },
		{ item_id = 114022, item_count = 1, weight = 1000 },
		{ item_id = 114023, item_count = 1, weight = 1000 },
		{ item_id = 114024, item_count = 1, weight = 1000 },
		{ item_id = 114025, item_count = 1, weight = 1000 },
		{ item_id = 114026, item_count = 1, weight = 1000 },
	};
	
	-- 计算总权重
	local totalweight = 0;
	for index,item in ipairs(arr_items) do
		if item.item_id and item.item_count and item.weight and item.weight > 0 then
			totalweight = totalweight + item.weight;
		else
			print("BlackIron_Normal is worng in totalweight");
			return 0;
		end
	end
	-- print("totalweight: ".. totalweight);
	
	-- 随机数
	local random_number = math.random(totalweight);
	
    -- 使用累计权重方法选择物品
    local accumulated_weight = 0
    local selected_item = nil
	
	-- 随机
    for _, item in ipairs(arr_items) do
        accumulated_weight = accumulated_weight + item.weight
        if random_number <= accumulated_weight then
            selected_item = item
            break
        end
    end
	
    -- 添加物品
    if selected_item then
		-- 判断保底
		if bao_di_open == true then
			local check_var = pRole:GetVariable(bao_di_checkvariable);
				-- print("debug: bao_di old check_var: "..check_var);
			
			-- 判断保底次数
			if check_var >= bao_di_counts then
				-- print("debug: bao_di Success");
				
				-- 保底成功
				pRole:GetItemBag():AddItem(bao_di_item_id, bao_di_item_count, ITEMLOG_PACKAGE, bao_di_item_id, false);
				pRole:SetVariable(bao_di_checkvariable, 0);  -- 保底清零
				
				pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "黑铁盲盒，保底成功！");	
			else
				print("debug: bao_di Fail");
				
				pRole:GetItemBag():AddItem(selected_item.item_id, selected_item.item_count, ITEMLOG_PACKAGE, selected_item.item_id, false);
				-- print(string.format("选中物品: ID=%d, 数量=%d", selected_item.item_id, selected_item.item_count));
				
				-- 保底失败
				check_var = check_var + 1;
				pRole:SetVariable(bao_di_checkvariable, check_var);
				-- print("debug: bao_di now check_var: "..check_var);
			end
		else
			-- 没有保底
			pRole:GetItemBag():AddItem(selected_item.item_id, selected_item.item_count, ITEMLOG_PACKAGE, selected_item.item_id, false);
			-- print(string.format("选中物品: ID=%d, 数量=%d", selected_item.item_id, selected_item.item_count));
		end
    end
	
	return errSuccess;
end

-- 2000024-命运武器礼盒
function DestinyWeapon(pItem, pRole)
	local itemID = 0;
	local selected_level = nil;
	local bagObj = pRole:GetItemBag();
	
	-- 判断职业
	local roleClass = pRole:GetClass();
	if roleClass == clsWarrior then
		itemID = 99900030;  -- 命运之刃
	elseif roleClass == clsMage then
		itemID = 99900046;  -- 命运之杖
	elseif roleClass == clsTaoist then
		itemID = 99900047;  -- 命运之幡
	end
	
	-- 不同职业, 概率不一样
	if roleClass == clsWarrior then
		-- 战士
		local arr_levels = 
		{
			{ weapon_level = 0, weight = 82500 },
			{ weapon_level = 1, weight = 4375  },
			{ weapon_level = 2, weight = 3750  },
			{ weapon_level = 3, weight = 3125  },
			{ weapon_level = 4, weight = 2500  },
			{ weapon_level = 5, weight = 1875  },
			{ weapon_level = 6, weight = 1250  },
			{ weapon_level = 7, weight = 625   },
		};
		
		-- 计算总权重
		local totalweight = 0;
		for index,selectLevel in ipairs(arr_levels) do
			if selectLevel.weight > 0 then
				totalweight = totalweight + selectLevel.weight;
			else
				print("DestinyWeapon is worng in totalweight");
				return 0;
			end
		end
		
		-- 随机数
		local random_number = math.random(totalweight);
		
		-- 使用累计权重方法选择物品
		local accumulated_weight = 0;
		
		-- 随机
		for _, selectLevel in ipairs(arr_levels) do
			accumulated_weight = accumulated_weight + selectLevel.weight;
			if random_number <= accumulated_weight then
				selected_level = selectLevel;
				break;
			end
		end
	
	elseif roleClass == clsMage or roleClass == clsTaoist then
		-- 法师/道士
		local arr_levels = 
		{
			{ weapon_level = 0, weight = 94525 },
			{ weapon_level = 1, weight = 3750  },
			{ weapon_level = 2, weight = 350   },
			{ weapon_level = 3, weight = 325   },
			{ weapon_level = 4, weight = 300   },
			{ weapon_level = 5, weight = 275   },
			{ weapon_level = 6, weight = 250   },
			{ weapon_level = 7, weight = 225   },
		};
		
		-- 计算总权重
		local totalweight = 0;
		for index,selectLevel in ipairs(arr_levels) do
			if selectLevel.weight > 0 then
				totalweight = totalweight + selectLevel.weight;
			else
				print("DestinyWeapon is worng in totalweight");
				return 0;
			end
		end
		
		-- 随机数
		local random_number = math.random(totalweight);
		
		-- 使用累计权重方法选择物品
		local accumulated_weight = 0;
		
		-- 随机
		for _, selectLevel in ipairs(arr_levels) do
			accumulated_weight = accumulated_weight + selectLevel.weight;
			if random_number <= accumulated_weight then
				selected_level = selectLevel;
				break;
			end
		end
		
	end
	
	-- 获得命运武器
	pRole:GetItemBag():AddDestinyWeapon(itemID, selected_level.weapon_level);
	
	return errSuccess;
end

-- 2000025-赞助礼盒288
function AddTitle_288(pItem, pRole)
	pRole:GetTitle():AddTitle(44);  -- 人位境界-44
	return errSuccess;
end

-- 2000025-赞助礼盒488
function AddTitle_488(pItem, pRole)
	pRole:GetTitle():AddTitle(50);  -- 灵者境界-50
	return errSuccess;
end

-- 2000025-赞助礼盒888
function AddTitle_888(pItem, pRole)
	pRole:GetTitle():AddTitle(47);  -- 圣徒境界-47
	return errSuccess;
end

-- 2000031-元宝袋(1.00)
function YuanBaoDai_100(pItem, pRole)
	pRole:GetItemBag():AddMoney(MONEYTYPE_04, 100, MONEYLOG_PACKAGE, 0);
	return errSuccess;
end
-- 2000032-元宝袋10.00)
function YuanBaoDai_1000(pItem, pRole)
	pRole:GetItemBag():AddMoney(MONEYTYPE_04, 1000, MONEYLOG_PACKAGE, 0);
	return errSuccess;
end
-- 2000033-元宝袋100.00)
function YuanBaoDai_10000(pItem, pRole)
		pRole:GetItemBag():AddMoney(MONEYTYPE_04, 10000, MONEYLOG_PACKAGE, 0);
	return errSuccess;
end
-- 2000034-元宝袋1000.00)
function YuanBaoDai_100000(pItem, pRole)
	pRole:GetItemBag():AddMoney(MONEYTYPE_04, 100000, MONEYLOG_PACKAGE, 0);
	return errSuccess;
end

-- 2000035-元宝转化器(1.00)
function GmCmd_SubMoneyYuanBao_100(pItem, pRole)
	pRole:GetItemBag():SubMoney(MONEYTYPE_04, 100, MONEYLOG_GM_CMD_SUB_MONEY_YB, 0);
	pRole:GetItemBag():AddItem(2000031, 1, MONEYLOG_GM_CMD_ADD_ITEM_YBD, 2000031, false);
	return errItemUnknown;
end
-- 2000036-元宝转化器(10.00)
function GmCmd_SubMoneyYuanBao_1000(pItem, pRole)
	pRole:GetItemBag():SubMoney(MONEYTYPE_04, 1000, MONEYLOG_GM_CMD_SUB_MONEY_YB, 0);
	pRole:GetItemBag():AddItem(2000032, 1, MONEYLOG_GM_CMD_ADD_ITEM_YBD, 2000032, false);
	return errItemUnknown;
end
-- 2000037-元宝转化器(100.00)
function GmCmd_SubMoneyYuanBao_10000(pItem, pRole)
	pRole:GetItemBag():SubMoney(MONEYTYPE_04, 10000, MONEYLOG_GM_CMD_SUB_MONEY_YB, 0);
	pRole:GetItemBag():AddItem(2000033, 1, MONEYLOG_GM_CMD_ADD_ITEM_YBD, 2000033, false);
	return errItemUnknown;
end
-- 2000038-元宝转化器(1000.00)
function GmCmd_SubMoneyYuanBao_100000(pItem, pRole)
	pRole:GetItemBag():SubMoney(MONEYTYPE_04, 100000, MONEYLOG_GM_CMD_SUB_MONEY_YB, 0);
	pRole:GetItemBag():AddItem(2000034, 1, MONEYLOG_GM_CMD_ADD_ITEM_YBD, 2000034, false);
	return errItemUnknown;
end

-- 2000039-双倍经验丹(50万)
function DoubleJinYan50(pItem, pRole)
	pRole:AddExtraExp(500000)
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "你已获得50万的双倍经验,赶快去升级吧!");	
	return	errSuccess;
end
-- 2000040-双倍经验丹(100万)
function DoubleJinYan100(pItem, pRole)
	pRole:AddExtraExp(1000000)
	pRole:GetScene():Say(pRole:GetObjID(), cltTvShow, "你已获得100万的双倍经验,赶快去升级吧!");	
	return	errSuccess;
end

---------- 自己新增代码 end

	
Include("script/item/title.lua")
Include("script/item/package.lua")
Include("script/item/jump.lua")
Include("script/item/quest.lua")
