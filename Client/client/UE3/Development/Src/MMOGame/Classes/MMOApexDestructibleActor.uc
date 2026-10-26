//
// FracturedStaticMeshActor类
//

class MMOApexDestructibleActor extends ApexDestructibleActor implements(IAbilityDamageable)
	native
	placeable;

// 阵营标识, 两阵营标识做 AND 操作，不为0是友好
var int FriendlyMask;

var(MMO) int CurHealth;
var(MMO) int MaxHealth;     // 这个变量需要么？这玩意会回血么？zhaojun@snda

// 破坏后就隐藏阻挡
var(MMO) bool DisableCollisionWhenExplode;

event int GetFriendlyMask()
{
	return FriendlyMask;
}

// if processed return true, else false
event ProcessDamage(DamageData Damage)
{
//	var AbilityHitPointComponent AbilityData;
	local TraceHitInfo HitInfo;//vect(Damage.Attacker.Location-Location)
	local Vector dir;

	// added by zhaojun@snda, begin
	CurHealth -= Damage.DamageValue;

	CurHealth = CurHealth > 0 ? CurHealth : 0;
	CurHealth = CurHealth < MaxHealth ? CurHealth : MaxHealth;
	//Clamp(CurHealth, 0, MaxHealth);
	// added by zhaojun@snda, end

	dir = Normal(Location - Damage.BaseActor.Location) * Damage.DamageValue;
	TakeDamage(Damage.DamageValue, None, Location, dir, class'DmgType_Crushed', HitInfo, self);

	if (CurHealth == 0)
	{
		if(DisableCollisionWhenExplode)
		{
			// TODO: add health determinate
			SetCollision(false, false, true);
		}
	}
}

event bool IsDead()
{
	if(LifeSpan < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

cpptext
{
	virtual void TickAuthoritative( FLOAT DeltaSeconds );
	virtual void TakeDamage(INT Damage,class AController* EventInstigator,FVector HitLocation,FVector Momentum,class UClass* DamageType,struct FTraceHitInfo HitInfo=FTraceHitInfo(EC_EventParm),class AActor* DamageCauser=NULL);
	virtual void TakeRadiusDamage(class AController* InstigatedBy,FLOAT BaseDamage,FLOAT DamageRadius,class UClass* DamageType,FLOAT Momentum,FVector HurtOrigin,UBOOL bFullDamage,class AActor* DamageCauser,FLOAT DamageFalloffExponent=1.000000);
   
}


defaultproperties
{
	FriendlyMask=4
	DisableCollisionWhenExplode=true
	CurHealth = 1;  // 默认情况一打就碎
	MaxHealth = 1;  // 默认情况一打就碎
}
