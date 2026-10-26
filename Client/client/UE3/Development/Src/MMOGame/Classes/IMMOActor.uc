
interface IMMOActor
	native;


// 角色类型，可能会影响某些攻击计算
enum EActorClassType
{
	// 没有
	EACT_None <DisplayName="None">,
	
	// 场景物体
	EACT_SceneObject <DisplayName="SceneObject">,

	// 玩家自己
	EACT_PlayerSelf <DisplayName="PlayerSelf">,

	// 其它玩家
	EACT_OtherPlayer <DisplayName="OtherPlayer">,

	// 公务NPC
	EACT_NPC <DisplayName="NPC">,

	// 普通怪
	EACT_Monster <DisplayName="Monster">,

	// BOSS
	EACT_Boss <DisplayName="Boss">,

	// 怪物尸体
	EACT_MonsterBody <DisplayName="MonsterBody">,

	// NPC尸体
	EACT_NPCBody <DisplayName="NPCBody">,

	// Player尸体
	EACT_PlayerBody <DisplayName="PlayerBody">,

	// Doodad
	EACT_Doodad <DisplayName="Doodad">,

	// 掉落物品
	EACT_DropItem <DisplayName="DropItem">,

	// TOY
	EACT_Toy <DisplayName="Toy">,

	// 宠物
	EACT_Pet <DisplayName="Pet">,

	// 功能NPC
	EACT_Function_NPC <DisplayName="FNPC">,

	// GM（GM是比较特殊的，考虑后期做客服）
	EACT_GM  <DisplayName="GM">
};

native function EActorClassType GetActorType() const;