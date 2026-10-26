LoadPackage("role.pkg");
LoadPackage("item_bag.pkg");
LoadPackage("char_def.pkg");
LoadPackage("spell_book.pkg");
LoadPackage("spell.pkg")
LoadPackage("quest_list.pkg")
LoadPackage("achievement_def.pkg")
LoadPackage("achievement_list.pkg")

function main(oRole)
	local class = oRole:GetClass();
	local IsInDevMode = false
	local sex = oRole:GetSex();


	--! 解锁基本技能Slot
	oRole:UnlockSpellSlot(qssNormalAtk);
	oRole:UnlockSpellSlot(qssKey10); --原qssMouseL
	oRole:UnlockSpellSlot(qssKey11); --原qssMouseR
	oRole:UnlockSpellSlot(qssKey1);
	oRole:UnlockSpellSlot(qssKey2);
	oRole:UnlockSpellSlot(qssKey3);
	oRole:UnlockSpellSlot(qssKey4);
	oRole:UnlockSpellSlot(qssKey5);
	oRole:UnlockSpellSlot(qssKey6);
	oRole:UnlockSpellSlot(qssKey7);
	oRole:UnlockSpellSlot(qssKey8);
	oRole:UnlockSpellSlot(qssKey9);
	oRole:UnlockSpellSlot(qssKey0);
	oRole:UnlockSpellSlot(qssPassive1);
	oRole:UnlockSpellSlot(qssPassive2);
	oRole:UnlockSpellSlot(qssPassive3);

	--! 新手礼包
	oRole:GetItemBag():AddItem(331, 1, ITEMLOG_CREATE_ROLE, 0, false);
	oRole:GetItemBag():AddItem(331, 1, ITEMLOG_CREATE_ROLE, 0, false);
	oRole:GetItemBag():AddItem(331, 1, ITEMLOG_CREATE_ROLE, 0, false);
	oRole:GetItemBag():AddItem(331, 1, ITEMLOG_CREATE_ROLE, 0, false);
	oRole:GetItemBag():AddItem(331, 1, ITEMLOG_CREATE_ROLE, 0, false);

	local b = os.time();
	oRole:SetVariable(1006, b);    -- [老配置]里面没有这句代码, 不知道有啥作用
	
	--! 初始免费飞鞋次数, [老配置]里这句代码是没注释的
	--oRole:GetAchievementList():SetVariable(avdQuestFlytoZone, 3);
	
	--! 各职业初始金
	--oRole:GetItemBag():AddMoney(1, 10000, MONEYLOG_BIRTH, 0);

	--! 初始任务
	oRole:GetQuestList():Accept(1441);

	--! 反外挂初始化
	oRole:SetAntiCheatLevel(2);

	--! 测试用工具类技能
	--oRole:LearnSpell(5, 0, true);
	--oRole:LearnSpell(6, 0, true);
	--oRole:LearnSpell(7, 0, true);
	--oRole:LearnSpell(8, 0, true);
	--oRole:LearnSpell(9, 0, true);


	--! 测试用, 后面删除
	-- oRole:GetItemBag():AddMoney(1, 100000000, MONEYLOG_BIRTH, 0);    -- 金币 1000万
	-- oRole:GetItemBag():AddMoney(3, 10000000, MONEYLOG_BIRTH, 0);    -- 元宝 10万
	

	--! 配置人物
	if not IsInDevMode then

		-- 战士角色配置
		if class == clsWarrior then

			oRole:SetLevel(1);

			-- 战士主动技
			oRole:LearnSpell(1030, 0, true);
			oRole:EquipSpell(qssNormalAtk, 1030);

			-- 左键替换技能
			--oRole:LearnSpell(1430, 0, true); -- 攻杀效果
			--oRole:LearnSpell(1431, 0, true); -- 刺杀效果
			---oRole:LearnSpell(1440, 0, true); -- 刺杀效果2
			--oRole:LearnSpell(1432, 0, true); -- 半月效果
			--oRole:LearnSpell(1433, 0, true); -- 烈火效果
			--oRole:LearnSpell(1434, 0, true); -- 逐日效果
			-- 角色装备
			if sex==1 then  --男 1
				oRole:GetItemBag():EquipItemOnBirth(89980113, NES_BODY); -- 上衣
			else		--女 2
				oRole:GetItemBag():EquipItemOnBirth(89990113, NES_BODY); -- 上衣
			end

		--	oRole:GetItemBag():EquipItemOnBirth(99800021, NES_MAIN_HAND); -- 并持短柄重型双手
		  --  oRole:GetItemBag():EquipItemOnBirth(10111111, NES_HEAD); -- 头
		  --  oRole:GetItemBag():EquipItemOnBirth(10111311, NES_BODY); -- 上衣
		 --   oRole:GetItemBag():EquipItemOnBirth(10111411, NES_LEG); -- 腿
		 --   oRole:GetItemBag():EquipItemOnBirth(10111511, NES_WAIST); -- 腰
		 --   oRole:GetItemBag():EquipItemOnBirth(10111611, NES_ARM); -- 腕
		 --   oRole:GetItemBag():EquipItemOnBirth(10111711, NES_FOOT); -- 鞋




			--背包
			oRole:GetItemBag():AddItem(89900001, 1, ITEMLOG_CREATE_ROLE, 0, false);

		-- 法师角色配置
		elseif class == clsMage then

			oRole:SetLevel(1);

			--法师主动技
			oRole:LearnSpell(2530, 0, true);
			oRole:EquipSpell(qssNormalAtk, 2530);

			oRole:GetItemBag():AddItem(89900001, 1, ITEMLOG_CREATE_ROLE, 0, false);

			-- 角色装备
			if sex==1 then  --男 1
				oRole:GetItemBag():EquipItemOnBirth(89980113, NES_BODY); -- 上衣
			else		--女 2
				oRole:GetItemBag():EquipItemOnBirth(89990113, NES_BODY); -- 上衣
			end

		-- 道士角色配置
		elseif class == clsTaoist then

			oRole:SetLevel(1);

			-- 道士主动技
			oRole:LearnSpell(3000, 0, true); -- 普通攻
			oRole:EquipSpell(qssNormalAtk, 3000);

			-- 角色装备
			if sex==1 then  --男 1
				oRole:GetItemBag():EquipItemOnBirth(89980113, NES_BODY); -- 上衣
			else		--女 2
				oRole:GetItemBag():EquipItemOnBirth(89990113, NES_BODY); -- 上衣
			end

			oRole:GetItemBag():AddItem(89900001, 1, ITEMLOG_CREATE_ROLE, 0, false);

			--oRole:GetItemBag():AddItem(40004, 1, ITEMLOG_CREATE_ROLE, 0, false);
			--oRole:GetItemBag():AddItem(40014, 1, ITEMLOG_CREATE_ROLE, 0, false);
			--oRole:GetItemBag():AddItem(40103, 1, ITEMLOG_CREATE_ROLE, 0, false);

			--oRole:LearnSpell(3400, 0, true); -- 施毒后续

		-- 刺客角色配置
		elseif class == clsRogue then

			oRole:SetLevel(1);

			-- 刺客主动技
			oRole:LearnSpell(1500, 0, true); -- 普通攻
			oRole:EquipSpell(qssNormalAtk, 	1500);  -- 补偿机制

			oRole:GetItemBag():AddItem(99800002, 1, ITEMLOG_CREATE_ROLE, 0, false);

		-- 弓手角色配置
		elseif class == clsArcher then

			oRole:SetLevel(1);

			-- 弓手主动技
			oRole:LearnSpell(2000, 0, true); -- 普通攻
			oRole:EquipSpell(qssNormalAtk, 	2000);  -- 补偿机制

			oRole:GetItemBag():AddItem(99800003, 1, ITEMLOG_CREATE_ROLE, 0, false);
		end

	end

end
