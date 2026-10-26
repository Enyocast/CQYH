/*
 * 游戏里通用配置数据
 * 
 * 
 */
class GamePlayInfo extends Object
	editinlinenew;

// 动画集数据
struct AnimSetInfo
{
	var() EPlayerClass Type;
	var() AnimSet Set;
};

var() array<AnimSetInfo> SetInfos;


// 武器姿态后缀名
struct EWeaponPoseString
{
	//var() EWeaponPoseType PoseType;
	var() string str;
};

var() array<EWeaponPoseString> WeaponPoseStringInfos;







function AnimSet GetAnimSet(EPlayerClass e)
{
	local int i;
	for(i = 0; i < SetInfos.Length; ++i)
	{
		if(e == SetInfos[i].Type && SetInfos[i].Set != none)
		{
			return SetInfos[i].Set;
		}
	}
	return none;
}
