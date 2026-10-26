LoadPackage("hero.pkg");
LoadPackage("role.pkg");
LoadPackage("char_def.pkg");
LoadPackage("hero_def.pkg");
LoadPackage("item_bag.pkg");
LoadPackage("spell_book.pkg");
LoadPackage("spell.pkg")

function main(oRole, oHero)
	print("Hero Created");

	local class = oHero:GetClass();

	if class == clsWarrior then

		-- 提供角色武器
		oRole:GetItemBag():EquipHeroItemOnBirth(10110211, NES_MAIN_HAND); -- 并持短柄重型类(双手剑)

		-- 刺客角色配置
	elseif class == clsRogue then

		-- 提供角色武器			
		oRole:GetItemBag():EquipHeroItemOnBirth(10120211, NES_MAIN_HAND); -- 双持匕首

		-- 弓手角色配置
	elseif class == clsArcher then

		-- 提供角色武器	
		oRole:GetItemBag():EquipHeroItemOnBirth(10130111, NES_MAIN_HAND); -- 双持弩

		-- 法师角色配置
	elseif class == clsMage then

		-- 提供角色武器	
		oRole:GetItemBag():EquipHeroItemOnBirth(10140311, NES_MAIN_HAND); -- 法杖类		

	end

end
