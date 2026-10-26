LoadPackage("common.pkg");
LoadPackage("gameworld.pkg");
LoadPackage("scene.pkg");
LoadPackage("scene_object.pkg");
LoadPackage("character.pkg");
LoadPackage("role.pkg");
LoadPackage("item_bag.pkg");


local SelfPlayer = nil;
local GameWorld = nil;



function Init()
		GameWorld = CGameWorld:GetInstance();
		print("Init..............");
end

function login()
		print("Login..............");

		SelfPlayer = GameWorld:NewRole(100);

		if SelfPlayer == nil then
				print("Create Self Role Failed");
				return;
		end

		print("Role Create Succeed");
		SelfPlayer:Init(100, nil);

		SelfPlayer:SetX(131072 * 68.15);
		SelfPlayer:SetY(131072 * 58.54);
		SelfPlayer:SetZ(131072 * 0.8);

		SelfPlayer:AddExp(1000);

		local Scene = GameWorld:FindScene(65537);
		if Scene == nil then
			print("No scene");
			return;
		end

		local ret = Scene:AddRole(SelfPlayer);

		if ret == false then
			print("Login failed!");
			return;
		end

		print("Login Succeed");
end

function learn(id, level)
		local ret = SelfPlayer:LearnSpell(id, level);
		if ret == nil then
				print("Learning spell failed");
		end
		print("Spell Learnt: "..tostring(id).."-"..tostring(level));
end

function addrole(id)
		print("Add Role");

		local role = GameWorld:NewRole(id);

		if role == nil then
				print("Create Role Failed");
				return;
		end

		role:Init(id, nil);

		role:SetX(131072 * 68.15);
		role:SetY(131072 * 58.54);
		role:SetZ(131072 * 0.8);

		local Scene = GameWorld:FindScene(65537);
		if Scene == nil then
			print("No scene");
			return;
		end

		local ret = Scene:AddRole(role);

		if ret == nil then
			print("add role failed!");
			return;
		end

		print("Add role succeed");
end

function cast_target(id, level, targetid)
		local target = GameWorld:FindCharacter(targetid);

		if target == nil then
				print("Invalid target");
				return;
		end
		print("target found");

		SelfPlayer:CastSpell(id, level, target, 0, 0, 0);
end

function cast_pos(id, level, x, y, z)
		SelfPlayer:CastSpell(id, level, nil, x, y, z);
end

function tf()
		login();
		learn(2027, 1);

		addrole(101);

		local x, y, z;
		x = SelfPlayer:GetX();
		y = SelfPlayer:GetY();
		z = SelfPlayer:GetZ();

		cast_pos(2027, 1, x, y, z);
end

function add_item(id, count)
		SelfPlayer:GetItemBag():AddItem(id, count)
end

function add_exp(nExp)
	SelfPlayer:AddExp(nExp);
end
