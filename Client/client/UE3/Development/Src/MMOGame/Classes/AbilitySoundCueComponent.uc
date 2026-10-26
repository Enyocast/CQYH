class AbilitySoundCueComponent extends AbilityComponent
	hidecategories(Object)
	editinlinenew
	native;


enum ESoundPlayType
{
	// 播放武器挥舞音效(由武器决定)
	ESPT_WeaponUseSound,
	// 播放武器打击音效(由武器材质与被击BODY材质决定)
	ESPT_WeaponHitSound,
	// 播放自定义音效, Sounds数组里定义的
	ESPT_CustomSound,
	//...
	ESPT_ClothNoise,
	// 播放挖矿音效
	ESPT_MineHitSound,

};

var(SoundCueComponent) ESoundPlayType   SoundPlayType;
//
var(WeaponUseSound) int SoundIdx;
// 如果使用武器音效,这个属性不需要配置
var(CustomSound)  Array<SoundCue> Sounds;
var(CustomSound) array<SoundCueByElementaryType> SoundsByElementaryType;

var(CustomSound) SoundCue EndSound;

var(ClothNoise) ENoiseActionType ActionType;

// 如果音效类型是实时类型的,那么这个音效会在技能编辑器里效果,游戏里会使用实时音效
var(PreviewSound)   SoundCue    PreviewSound;

cpptext
{
	virtual FString GetResName();
	virtual struct BaseComponent* CreateCplusplusNode();

	UBOOL GetSoundCueByElementaryType(BYTE InType, TArray<USoundCue*>& SoundList);
}

DefaultProperties
{
	LineColor=(R=0.0,G=0.6353,B=0.9098,A=1.0)
	TitleString="Sound"
	bHaveTrail=true
}
