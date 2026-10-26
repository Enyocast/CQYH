//
// 音效通知扩展类
//
class AnimNotify_SoundEx extends AnimNotify_Scripted;

/*
 * search soundCue by CharacterType and MaterialType and ActionType
 * for example
 * CharacterType    : male, female, normal npc, boss, super boss
 * ActionType       : land, walksound..
 * MaterialType     : water, stone...
 */
struct SoundSearchKey
{
	var() name CharacterType;
	var() name ActionType;
	var() name MaterialType;
};

//直接播放的音效
var(CommonSound)	array<SoundCue> 	SoundCues;
/*通过对象类型,行为,材质类型进行匹配的识别参数,
 * 这个与SoundCues不可同时设置,如果SoundCues里有配置了音效数据,
 * 则SoundSearchKeys里的参数失效
 */
var(MaterialSound)  array<SoundSearchKey>   SoundSearchKeys;
// 当有机会播放时,会从SoundCues里随机选取一种音效进行播放
var()   float       Rate;
var()	bool		bFollowActor;
var()	Name		BoneName;
var()	bool		bIgnoreIfActorHidden;

/** This is the percent to play this Sound.  Defaults to 100% (aka 1.0f) **/
var()   float       PercentToPlay;
var()   float		VolumeMultiplier;
var()	float		PitchMultiplier;

var transient int idx;
var transient SoundCue ToPlaySound;



function int GetNewSoundCueIdx()
{
	if(Rate < FRand())
	{
		return -1;
	}
	if(SoundCues.Length <= 0)
	{
		if(SoundSearchKeys.Length <= 0)
		{
			return -1;
		}
		else
		{
			return Rand(SoundSearchKeys.Length);
		}
	}
	else
	{
		return Rand(SoundCues.Length);
	}
}

event Notify( Actor Owner, AnimNodeSequence AnimSeqInstigator )
{
	local MMOSoundManager smgr;
	local MMOActor actor;
	local AudioComponent audio;

	actor = MMOActor(Owner);
	smgr = MMOGame(Owner.WorldInfo.Game).SoundManager;

	if(bIgnoreIfActorHidden)
	{
		if(Owner.bHidden)
		{
			return;
		}
	}

	idx = GetNewSoundCueIdx();
	if(idx == -1)
	{
		return;
	}
	else
	{
		if(SoundCues.Length > 0)
		{
			ToPlaySound = SoundCues[idx];	
		}
		else if(SoundSearchKeys.Length > 0)
		{
			ToPlaySound = smgr.GetSoundCue(SoundSearchKeys[idx].CharacterType, SoundSearchKeys[idx].ActionType, SoundSearchKeys[idx].MaterialType);
			if(ToPlaySound == none)
			{
				`warn("can not find SoundCue by "$SoundSearchKeys[idx].CharacterType $SoundSearchKeys[idx].ActionType $SoundSearchKeys[idx].MaterialType);
				return;
			}
		}
		else
		{
			`warn("AnimNotify_SoundEx :１０５　no sound date to play");
		}
	}



	if((smgr != none) && (actor != none))
	{
		smgr.PlaySoundFX(Owner, AnimSeqInstigator, self);
	}
	else
	{
		audio = Owner.CreateAudioComponent(ToPlaySound);
		if(audio != none)
		{
			if( BoneName != '' )
			{
				audio.bUseOwnerLocation	= false;
				audio.Location = AnimSeqInstigator.SkelComponent.GetBoneLocation(BoneName, 0);
			}
			else if( !(bFollowActor && (Owner != none)) )
			{	
				audio.bUseOwnerLocation	= false;
				audio.Location = Owner.Location;// AnimSeqInstigator.SkelComponent.LocalToWorld.GetOrigin();
			}
			audio.bAllowSpatialization = audio.bAllowSpatialization && !Owner.WorldInfo.bBegunPlay;
			audio.bAutoDestroy = true;
			audio.VolumeMultiplier = VolumeMultiplier;
			audio.PitchMultiplier = PitchMultiplier;
			//audio.PlaybackTime = cue.GetCueDuration() * PercentToPlay;
			audio.Play();
		}
	}
}

event NotifyEnd( Actor Owner, AnimNodeSequence AnimSeqInstigator )
{
	
}

DefaultProperties
{
	NotifyColor=(R=255,G=255,B=0,A=255)

	PercentToPlay=1.0f
	VolumeMultiplier=1.f
	PitchMultiplier=1.f
	bFollowActor=TRUE
	Rate=1.f
	bIgnoreIfActorHidden=true
}
