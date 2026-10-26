//
// IAbilityDamageable接口，能受伤的对象可实现此接口
//
interface IAbilityDamageable
	dependson(TypeDefine)
	native;


// damage data
struct native DamageData
{
	// 是否是服务器判定的伤害数据
	var bool bServerDamageData;
	// 伤害制造者,可能是玩家,可能是NPC, 可能是场景里的陷阱等
	var Actor BaseActor;
	var int CreatorId;
	// 伤害数值
	var int DamageValue;
	var EDamageResultType DamageType;
	// 主要是考虑客户端的血量与服务器的血量值有可能不一致,以至于不太相信客户端血为0时,就表示死亡, 因为这个重要信息,还是由服务器发来
	var bool bCauseDead;
	// 打击效果模版
	var AbilityHitPointComponent AbilityData;

	var EElementaryType ElementaryType;
};

// 取得阵营标识，以计算伤害
event int GetFriendlyMask();

// if processed return true, else false
event ProcessDamage(DamageData Damage);

event bool IsDead();