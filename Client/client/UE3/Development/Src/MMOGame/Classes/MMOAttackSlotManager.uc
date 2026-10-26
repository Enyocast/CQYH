// 使近战攻击者在被攻击者周围站成一圈进行攻击

class MMOAttackSlotManager extends Object
	native;

var int     SlotNum;
var float   SlotAngleDiff;
var int     Slots[10];

var MMOActor    OwnerActor;

event PostBeginPlay( )
{
	local int i;
	for( i = 0; i < SlotNum; ++i )
	{
		Slots[i] = 0;   // 0: empty
	}
}

function bool TakeProperSlot( Vector attacker, out float rst, out int slot )
{
	local Vector dir;
	local float t;
	local float angle;
	local int iround;
	local int irand;
	local int count;
	local int temp;

	dir = attacker - OwnerActor.Location;
	t = dir.Y / dir.X;
	angle = atan( t );
	if( dir.X < 0 )
		angle += 3.14;
	else if( dir.Y < 0 )
		angle += 4.71;
	t = angle / SlotAngleDiff;
	iround = Round( t );
	if( Slots[iround] == 0 )
	{
		rst = SlotAngleDiff * iround;
		Slots[iround] += 1;
		slot = iround;
		return true;
	}
	else
	{   // 左右各5格内随机三次
		irand = 5 - Rand( 10 );
		count = 3;
		temp = iround + irand;
		if( temp >= SlotNum )
			temp -= SlotNum;
		else if( temp < 0 )
			temp += SlotNum;
		while( Slots[temp] >= 1 && count != 0 )
		{
			irand = 5 - Rand( 10 );
			temp = iround + irand;
			if( temp >= SlotNum )
				temp -= SlotNum;
			else if( temp < 0 )
				temp += SlotNum;
			--count;
		}
		if( count == 0 )
		{   // 没有随机到合适位置 站原地了
			slot = -1;
			return false;
			//// 在周围一圈选一个随机位置(怪引得多了，被夹击的几率也就高了)
			//irand = Rand( SlotNum - 1 );
			//rst = SlotAngleDiff * irand;
			//Slots[irand] += 1;
			//slot = irand;
			//return true;
		}
		else
		{
			rst = SlotAngleDiff * temp;
			Slots[temp] += 1;
			slot = temp;
			return true;
		}
	}
}

function FreeSlot( int slot )
{
	//Slots[slot] -= 1;
	Slots[slot] = 0;
}

function FreeAll( )
{
	local int i;
	for( i = 0; i < SlotNum; ++i )
	{
		Slots[i] = 0;   // 0: empty
	}
}

DefaultProperties
{
	OwnerActor=none
	SlotNum=10
	SlotAngleDiff=0.628
}
