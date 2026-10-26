class DamageProcessData extends Object
	dependson(TypeDefine)
	hidecategories(Object)
	editinlinenew
	native;


struct native DamageEffectPair
{
	var(Common)     EDamageResultType ResultType;
	var(Damage)     EWeaponHitType    WeaponHitType;
	var(Damage)     EHitDirectionType DirectionType;
	var(Elementary) EElementaryType   ElementaryType;

	var(Common) editinline array<AbilityComponent> EffectList;
};

var() editinline  array<DamageEffectPair> DamageEffectList;

// state death data
struct native StateDeath
{
	var() EAURA_EFFECT_TYPE BuffType;
	var() editinline array<AbilityComponent> EffectList;
};

var() array<StateDeath> StateDeaths;

struct native CommonDeath
{
	var() DeathStyle DeathType;
	var() EElementaryType ElementaryType;
	var() editinline array<AbilityComponent> EffectList;
};

var() array<CommonDeath> CommonDeaths;

struct native BloodEffectNode
{
	var() EBloodEffectType BloodEffectType;
	var() editinline array<AbilityComponent> HitEffects;
};

struct native BloodEffect
{
	var() float NormalBloodPlayRate;
	var() array<BloodEffectNode>    NormalHitEffects;

	var() array<BloodEffectNode>    CritialHitEffects;

	var() array<BloodEffectNode>    DeadHitEffects;
};

var() BloodEffect   HitBloodEffect;




defaultproperties
{
}
