LoadPackage("attribute_def.pkg");
LoadPackage("spell.pkg");
LoadPackage("character.pkg");
LoadPackage("role.pkg");
LoadPackage("gameworld.pkg");
LoadPackage("char_def.pkg");

local OnlineUser = {};
local OnlineRole = {};
local RoleNamePrefix = {};
local RoleCount = {};
local GlobalPassiveSpell = {};
local GlobalActiveSpell = {};
local PassiveSpell = {};
local SpellSlotBind = {};
local PassiveSpellIndex = {};
local SpellConfig;

RoleNamePrefix[clsWarrior] = "W";
RoleNamePrefix[clsMage] = "M";
RoleNamePrefix[clsRogue] = "R";
RoleNamePrefix[clsArcher] = "A";

RoleCount[clsWarrior] = 100;
RoleCount[clsMage] = 100;
RoleCount[clsRogue] = 100;
RoleCount[clsArcher] = 100;

SpellSlotBind[clsWarrior] = {};
SpellSlotBind[clsMage] = {};
SpellSlotBind[clsRogue] = {};
SpellSlotBind[clsArcher] = {};

GlobalPassiveSpell[clsWarrior] = {};
GlobalPassiveSpell[clsMage] = {};
GlobalPassiveSpell[clsRogue] = {};
GlobalPassiveSpell[clsArcher] = {};

GlobalActiveSpell[clsWarrior] = {};
GlobalActiveSpell[clsMage] = {};
GlobalActiveSpell[clsRogue] = {};
GlobalActiveSpell[clsArcher] = {};

PassiveSpell[clsWarrior] = {};
PassiveSpell[clsMage] = {};
PassiveSpell[clsRogue] = {};
PassiveSpell[clsArcher] = {};

GlobalActiveSpell[clsWarrior] = {};
GlobalActiveSpell[clsMage] = {};
GlobalActiveSpell[clsRogue] = {};
GlobalActiveSpell[clsArcher] = {};

PassiveSpell[clsWarrior][0] = {};
PassiveSpell[clsWarrior][1] = {};
PassiveSpell[clsWarrior][2] = {};
PassiveSpell[clsWarrior][3] = {};

PassiveSpell[clsMage][0] = {};
PassiveSpell[clsMage][1] = {};
PassiveSpell[clsMage][2] = {};
PassiveSpell[clsMage][3] = {};

PassiveSpell[clsRogue][0] = {};
PassiveSpell[clsRogue][1] = {};
PassiveSpell[clsRogue][2] = {};
PassiveSpell[clsRogue][3] = {};

PassiveSpell[clsArcher][0] = {};
PassiveSpell[clsArcher][1] = {};
PassiveSpell[clsArcher][2] = {};
PassiveSpell[clsArcher][3] = {};

PassiveSpellIndex[clsWarrior] = {};
PassiveSpellIndex[clsMage] = {};
PassiveSpellIndex[clsRogue] = {};
PassiveSpellIndex[clsArcher] = {};

PassiveSpellIndex[clsWarrior][0] = 1;
PassiveSpellIndex[clsWarrior][1] = 1;
PassiveSpellIndex[clsWarrior][2] = 1;
PassiveSpellIndex[clsWarrior][3] = 1;

PassiveSpellIndex[clsMage][0] = 1;
PassiveSpellIndex[clsMage][1] = 1;
PassiveSpellIndex[clsMage][2] = 1;
PassiveSpellIndex[clsMage][3] = 1;

PassiveSpellIndex[clsRogue][0] = 1;
PassiveSpellIndex[clsRogue][1] = 1;
PassiveSpellIndex[clsRogue][2] = 1;
PassiveSpellIndex[clsRogue][3] = 1;

PassiveSpellIndex[clsArcher][0] = 1;
PassiveSpellIndex[clsArcher][1] = 1;
PassiveSpellIndex[clsArcher][2] = 1;
PassiveSpellIndex[clsArcher][3] = 1;

PassiveSpellSlotTable =
{
	qssPassive1,
	qssPassive2,
	qssPassive3
};

ActiveSpellSlotTable = 
{
	qssMouseL,
	qssMouseR,
	qssKey1,
	qssKey2,
	qssKey3,
	qssKey4,
	qssKey5,
	qssKey6,
	qssKey7,
	qssKey8,
	qssKey9,
	qssKey0,
};

function _DoSubset(subset, cls, idx)
	local out = {};
	for n = 1, table.getn(subset) do
		out[n] = subset[n];
	end

	table.insert(PassiveSpell[cls][idx], out);
end

function _ChooseAll(cls, idx, from, n, to, count)
	--print("choose all: ".. n .. ", " .. count);

	if count <= 0 then
		_DoSubset(to, cls, idx);
		return;
	end

	for k = n, count, -1 do
		to[count] = from[k];
		if k >= 1 then
			_ChooseAll(cls, idx, from, n - 1, to, count - 1);
		else
			_DoSubset(to, cls, idx);
		end
	end
end

function _FillPassiveSpell()
	for cls = clsPlayerBegin, clsPlayerEnd - 1 do
		for n = 1, 3 do
			local ret = true;
			local s = {};
			_ChooseAll(cls, n, GlobalPassiveSpell[cls], table.getn(GlobalPassiveSpell[cls]), s, n);
		end
	end
end

function _ActivateAndEquipRune(i, spellid, runeslot)
	OnlineUser[i]:ActivateRune(spellid, runeslot);
    msg = recv_msg(5, OnlineUser[i]:GetSessionID(), protocol.g2c_rune_activate);
    check(msg, "failed to  recv g2c_rune_activate:" .. i .. ", spellid: " .. spellid .. ", runeslot: " .. runeslot);
	check(msg.nErrCode == errSuccess, "failed to activate rune: " .. i .. ", spellid: " .. spellid .. ", runeslot: " .. runeslot);
	
	OnlineUser[i]:EquipRune(spellid, runeslot);
	msg = recv_msg(5, OnlineUser[i]:GetSessionID(), protocol.g2c_equip_rune);
    check(msg, "failed to  recv g2c_equip_rune: " .. i .. ", spellid: " .. spellid .. ", runeslot: " .. runeslot);
	check(msg.nErrCode == errSuccess, "failed to activate rune: " .. i .. ", spellid: " .. spellid .. ", runeslot: " .. runeslot);
end

function _EquipSpell(i, spellid, slotid)
	OnlineUser[i]:EquipSpell(slotid, spellid);
--    msg = recv_msg(5, OnlineUser[i]:GetSessionID(), protocol.g2c_equip_spell);
 --   check(msg, "failed to  recv g2c_equip_spell:" .. i .. ", spellid: " .. spellid .. ", slot: " .. slotid);
	--check(msg.nErrCode == errSuccess, "failed to equipspell: " .. i .. ", spellid: " .. spellid .. ", slot: " .. slotid);
end

function _CastSpell(i, slotid, target)
	OnlineUser[i]:CastSpell(slotid, target:GetObjID(), target:GetX(), target:GetY(), target:GetZ());
end

function _Update(cls, n, i)
	local Name = RoleNamePrefix[cls] .. i .. "_" .. os.date("%H%M%S");
	print(Name);

	OnlineUser[n], OnlineRole[n] = startup(Name, Name, nil, cls);
	check(OnlineUser[n], "failed to create user");
	check(OnlineRole[n], "failed to create role");

	OnlineUser[n]:GMCommand(".level 40");
	OnlineUser[n]:GMCommand(".jump lgsm");

	msg = recv_msg(60, OnlineUser[n]:GetSessionID(), protocol.g2c_enter_scene)
	check(msg, "failed to recv g2c_enter_scene");

	local mod = i % 4;
	if mod ~= 0  then
		if PassiveSpellIndex[cls][mod] > table.getn(PassiveSpell[cls][mod]) then
			PassiveSpellIndex[cls][mod] = 1;
		end

		local tb = PassiveSpell[cls][mod][PassiveSpellIndex[cls][mod]];

		for j = 1, table.getn(tb) do
			_EquipSpell(n, tb[j], PassiveSpellSlotTable[j]);
		end
	end

end

function _DoCombat()
	print("begin combat");
	local n = 1;
	for cls = clsPlayerBegin, clsPlayerEnd - 1 do
		print("cls: " .. cls);
		for i = 1, RoleCount[cls] do
			--_Update(cls, n, i);
			addco("update_" .. cls .. ":" .. i, _Update, cls, n, i);
			n = n + 1;
		end
	end

	-- start combat
end

function CoverageTestCase.DoCombat()
	print("CoverageTestCase.DoCombat");
	math.randomseed(os.time());
	SpellConfig = CSpellConfig:GetInstance();

	SpellConfig:BeginSpell();
	while true do
		local SpellTemplate = SpellConfig:NextSpell();
		if SpellTemplate == nil then
			break;
		end

		for cls = clsPlayerBegin, clsPlayerEnd - 1 do
			if 2 ^ cls == SpellTemplate:GetAttr(satClass) and SpellTemplate:GetAttr(satCastType) == spctPassive and SpellTemplate:GetAttr(satCanEquip) == 1 then
				local exist = false;
				for i = 1, table.getn(GlobalPassiveSpell[cls]) do
					if GlobalPassiveSpell[cls][i] == SpellTemplate:GetID() then
						exist = true;
						break;
					end
				end
				if exist == false then
					table.insert(GlobalPassiveSpell[cls], SpellTemplate:GetID());
				end
			end

			if 2 ^ cls == SpellTemplate:GetAttr(satClass) and SpellTemplate:GetAttr(satCastType) == spctActive and SpellTemplate:GetAttr(satCanEquip) == 1 then
				local exist = false;
				for i = 1, table.getn(GlobalActiveSpell[cls]) do
					if GlobalActiveSpell[cls][i] == SpellTemplate:GetID() then
						exist = true;
						break;
					end
				end
				if exist == false then
					table.insert(GlobalActiveSpell[cls], SpellTemplate:GetID());
					table.insert(SpellSlotBind[SpellTemplate:GetAttr(satBindSlot)], SpellTemplate:GetID());
				end
			end
		end
	end

	_FillPassiveSpell();
	
	addco("DoCombat_E@WW", _DoCombat);
end

