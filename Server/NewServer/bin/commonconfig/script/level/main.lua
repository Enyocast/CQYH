LoadPackage("role.pkg");
LoadPackage("char_def.pkg");
LoadPackage("spell_book.pkg");
LoadPackage("spell.pkg");
LoadPackage("character.pkg");
LoadPackage("chat_def.pkg");
LoadPackage("item_bag.pkg");

local SlotTable = {};
SlotTable[49] = qssKey0;
SlotTable[50] = qssKey1;
SlotTable[51] = qssKey2;
SlotTable[52] = qssKey3;
SlotTable[53] = qssKey4;
SlotTable[54] = qssKey5;
SlotTable[55] = qssKey6;
SlotTable[56] = qssKey7;
SlotTable[57] = qssKey8;
SlotTable[58] = qssKey9;
SlotTable[59] = qssKey10;
SlotTable[60] = qssKey11;

--! 技能获取表
local WarriorSkillGet = {};
WarriorSkillGet[41] = 1031; -- 基础剑术
WarriorSkillGet[42] = 1032; -- 攻杀剑术
WarriorSkillGet[43] = 1033; -- 刺杀剑术
WarriorSkillGet[44] = 1034; -- 半月弯刀
WarriorSkillGet[45] = 1035; -- 野蛮冲撞
WarriorSkillGet[46] = 1036; -- 烈火剑法
WarriorSkillGet[47] = 1037; -- 狮子吼
WarriorSkillGet[48] = 1038; -- 逐日剑法
WarriorSkillGet[49] = 0--1039; -- 旋风斩
WarriorSkillGet[50] = 0--1040; -- 暴怒
WarriorSkillGet[51] = 0--1041; -- 盾墙
WarriorSkillGet[52] = 0;
WarriorSkillGet[53] = 0;
WarriorSkillGet[54] = 0;
WarriorSkillGet[55] = 0;
WarriorSkillGet[56] = 0;
WarriorSkillGet[57] = 0;
WarriorSkillGet[58] = 0;
WarriorSkillGet[59] = 0;
WarriorSkillGet[60] = 0;

local MageSkillGet = {};
MageSkillGet[41] = 2531; -- 火球术
MageSkillGet[42] = 2532; -- 抗拒火环
MageSkillGet[43] = 2541; -- 诱惑之光
MageSkillGet[44] = 2544; -- 地狱火
MageSkillGet[45] = 2533; -- 雷电术
MageSkillGet[46] = 2538; -- 瞬息移动
MageSkillGet[47] = 2545; -- 爆裂火焰
MageSkillGet[48] = 2534; -- 火墙
MageSkillGet[49] = 2536; -- 疾光电影
MageSkillGet[50] = 2546; -- 地狱雷光
MageSkillGet[51] = 2535; -- 魔法盾
MageSkillGet[52] = 2547; -- 圣言术
MageSkillGet[53] = 2537; -- 冰咆哮
MageSkillGet[54] = 2550; -- 寒冰掌
MageSkillGet[55] = 2549; -- 大火球
MageSkillGet[56] = 2539; -- 灭天火
MageSkillGet[57] = 2540; -- 流星火雨
MageSkillGet[58] = 0--2548; -- 月华
MageSkillGet[59] = 0--2542; -- 吞魔盾
MageSkillGet[60] = 0--2543; -- 魔力过载

local TaoistSkillGet = {};
TaoistSkillGet[41] = 3002; -- 治愈术
TaoistSkillGet[42] = 3001; -- 精神力战法
TaoistSkillGet[43] = 3004; -- 施毒术
TaoistSkillGet[44] = 3005; -- 灵魂火符
TaoistSkillGet[45] = 3003; -- 召唤死灵
TaoistSkillGet[46] = 3009; -- 隐身术
TaoistSkillGet[47] = 3014; -- 集体隐身术
TaoistSkillGet[48] = 3006; -- 幽灵盾
TaoistSkillGet[49] = 3007; -- 神圣战甲术
TaoistSkillGet[50] = 3011; -- 困魔阵
TaoistSkillGet[51] = 3018; -- 气功波
TaoistSkillGet[52] = 3012; -- 群体治愈术
TaoistSkillGet[53] = 3008; -- 召唤神兽
TaoistSkillGet[54] = 3015; -- 无极真气
TaoistSkillGet[55] = 3010; -- 噬血术
TaoistSkillGet[56] = 0--3016; -- 画地为牢
TaoistSkillGet[57] = 0--3017; -- 净化术
TaoistSkillGet[58] = 0--3013; -- 护体术
TaoistSkillGet[59] = 0;
TaoistSkillGet[60] = 0;

local RogueSkillGet = {};
RogueSkillGet[41] = 0;
RogueSkillGet[42] = 0;
RogueSkillGet[43] = 0;
RogueSkillGet[44] = 0;
RogueSkillGet[45] = 0;
RogueSkillGet[46] = 0;
RogueSkillGet[47] = 0;
RogueSkillGet[48] = 0;
RogueSkillGet[49] = 0;
RogueSkillGet[50] = 0;
RogueSkillGet[51] = 0;
RogueSkillGet[52] = 0;
RogueSkillGet[53] = 0;
RogueSkillGet[54] = 0;
RogueSkillGet[55] = 0;
RogueSkillGet[56] = 0;
RogueSkillGet[57] = 0;
RogueSkillGet[58] = 0;
RogueSkillGet[59] = 0;
RogueSkillGet[60] = 0;

local ArcherSkillGet = {};
ArcherSkillGet[41] = 0;
ArcherSkillGet[42] = 0;
ArcherSkillGet[43] = 0;
ArcherSkillGet[44] = 0;
ArcherSkillGet[45] = 0;
ArcherSkillGet[46] = 0;
ArcherSkillGet[47] = 0;
ArcherSkillGet[48] = 0;
ArcherSkillGet[49] = 0;
ArcherSkillGet[50] = 0;
ArcherSkillGet[51] = 0;
ArcherSkillGet[52] = 0;
ArcherSkillGet[53] = 0;
ArcherSkillGet[54] = 0;
ArcherSkillGet[55] = 0;
ArcherSkillGet[56] = 0;
ArcherSkillGet[57] = 0;
ArcherSkillGet[58] = 0;
ArcherSkillGet[59] = 0;
ArcherSkillGet[60] = 0;


local SkillTable = {WarriorSkillGet, MageSkillGet, RogueSkillGet, ArcherSkillGet, TaoistSkillGet};

--! 自动装配表
local WarriorSkillAutoEquip = {}
WarriorSkillAutoEquip[49] = 1033;
WarriorSkillAutoEquip[50] = 1034;
WarriorSkillAutoEquip[51] = 1035;
WarriorSkillAutoEquip[52] = 1036;
WarriorSkillAutoEquip[53] = 1037;
WarriorSkillAutoEquip[54] = 1038;
WarriorSkillAutoEquip[55] = 0;--1040;
WarriorSkillAutoEquip[56] = 0;--1039;
WarriorSkillAutoEquip[57] = 0;--1041;
WarriorSkillAutoEquip[58] = 0;
WarriorSkillAutoEquip[59] = 0;
WarriorSkillAutoEquip[60] = 0;

local MageSkillAutoEquip = {}
MageSkillAutoEquip[49] = 2531;
MageSkillAutoEquip[50] = 2532;
MageSkillAutoEquip[51] = 2541;
MageSkillAutoEquip[52] = 2544;
MageSkillAutoEquip[53] = 2533;
MageSkillAutoEquip[54] = 2538;
MageSkillAutoEquip[55] = 2545;
MageSkillAutoEquip[56] = 2534;
MageSkillAutoEquip[57] = 2536;
MageSkillAutoEquip[58] = 2546;
MageSkillAutoEquip[59] = 2535;
MageSkillAutoEquip[60] = 2547;

local TaoistSkillAutoEquip = {}
TaoistSkillAutoEquip[49] = 3002;
TaoistSkillAutoEquip[50] = 3004;
TaoistSkillAutoEquip[51] = 3005;
TaoistSkillAutoEquip[52] = 3003;
TaoistSkillAutoEquip[53] = 3009;
TaoistSkillAutoEquip[54] = 3014;
TaoistSkillAutoEquip[55] = 3006;
TaoistSkillAutoEquip[56] = 3007;
TaoistSkillAutoEquip[57] = 3011;
TaoistSkillAutoEquip[58] = 3018;
TaoistSkillAutoEquip[59] = 3012;
TaoistSkillAutoEquip[60] = 3008;

local RougeSkillAutoEquip = {}
RougeSkillAutoEquip[49] = 0;
RougeSkillAutoEquip[50] = 0;
RougeSkillAutoEquip[51] = 0;
RougeSkillAutoEquip[52] = 0;
RougeSkillAutoEquip[53] = 0;
RougeSkillAutoEquip[54] = 0;
RougeSkillAutoEquip[55] = 0;
RougeSkillAutoEquip[56] = 0;
RougeSkillAutoEquip[57] = 0;
RougeSkillAutoEquip[58] = 0;
RougeSkillAutoEquip[59] = 0;
RougeSkillAutoEquip[60] = 0;

local ArcherSkillAutoEquip = {}
ArcherSkillAutoEquip[49] = 0;
ArcherSkillAutoEquip[50] = 0;
ArcherSkillAutoEquip[51] = 0;
ArcherSkillAutoEquip[52] = 0;
ArcherSkillAutoEquip[53] = 0;
ArcherSkillAutoEquip[54] = 0;
ArcherSkillAutoEquip[55] = 0;
ArcherSkillAutoEquip[56] = 0;
ArcherSkillAutoEquip[57] = 0;
ArcherSkillAutoEquip[58] = 0;
ArcherSkillAutoEquip[59] = 0;
ArcherSkillAutoEquip[60] = 0;


local SkillEquipTable = {WarriorSkillAutoEquip, MageSkillAutoEquip, RougeSkillAutoEquip, ArcherSkillAutoEquip, TaoistSkillAutoEquip};


--! 升级执行逻辑
function main(oRole, old_level, new_level)

	--print("oldlevel: "..old_level..", newlevel: "..new_level);

	if new_level == 61 then

		local class = oRole:GetClass();

		if (new_level - old_level > 1) and class == clsTaoist then
			oRole:GetItemBag():AddItem(40004, 1, ITEMLOG_CREATE_ROLE, 0, false);
			oRole:GetItemBag():AddItem(40014, 1, ITEMLOG_CREATE_ROLE, 0, false);
			oRole:GetItemBag():AddItem(40103, 1, ITEMLOG_CREATE_ROLE, 0, false);
		end


		local classinskill = class + 1

		-- 升级功能
		for next_level = old_level + 1, new_level do

			-- 获得技能
			if SkillTable[classinskill][next_level] ~= nil then
				if type(SkillTable[classinskill][next_level]) == "number" then
					if SkillTable[classinskill][next_level] ~= 0 then
						oRole:LearnSpell(SkillTable[classinskill][next_level], 0, true);
					end
				elseif type(SkillTable[classinskill][next_level]) == "table" then
					for i =1, #SkillTable[classinskill][next_level] do
						if SkillTable[classinskill][next_level][i] ~= 0 then
							oRole:LearnSpell(SkillTable[classinskill][next_level][i], 0, true);
						end
					end
				end
			end


			-- 自动装配技能
			if SkillEquipTable[classinskill][next_level] ~= nil then

				if type(SkillEquipTable[classinskill][next_level]) == "number" then
					if type(SlotTable[next_level]) == "number" then
						oRole:EquipSpell(SlotTable[next_level], SkillEquipTable[classinskill][next_level]);
					elseif type(SlotTable[next_level]) == "table" then
						if type(SlotTable[next_level][1]) == "number" then
							oRole:EquipSpell(SlotTable[next_level][1], SkillEquipTable[classinskill][next_level]);
						end
					end
				elseif type(SkillEquipTable[classinskill][next_level]) == "table" then
					if type(SlotTable[next_level]) ~= "table" then
						print("slot num is not match skill equip");
					else
						local maxlength = #SkillEquipTable[classinskill][next_level];
						if maxlength < #SlotTable[next_level] then
							maxlength = #SlotTable[next_level]
						end
						for i = 1, maxlength do
							if type(SkillEquipTable[classinskill][next_level][i]) == "number" then
								oRole:EquipSpell(SlotTable[next_level][i], SkillEquipTable[classinskill][next_level][i]);
							end
						end
					end
				end
			end

		end
	end

---------根据玩家等级发邮件

	--17级VIP验证by.xxp
		--[[if new_level>= 17 then
			if oRole:GetVIPLevel() < 1 then
				oRole:SetLevel(16)
			end
		end
				





	--问卷调查by.xxp

		if new_level== 17 then
			if oRole:GetVIPLevel() < 1 then
				oRole:Say(oRole:GetObjID(), cltUrl, "Welcome to take survey:‘http://www.cqyh.info/toPayAccount.html?surveyId=9438’")
				end
		end]]--

end

