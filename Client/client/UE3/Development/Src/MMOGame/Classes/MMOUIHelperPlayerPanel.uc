class MMOUIHelperPlayerPanel extends MMOUIBase
	native(UI);

var string _CurHeadIcon;
var SoundCue _CurSound;
var bool _IsPlaying;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event CallUpdateHelperSoundData(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateHelperSoundData");
}

native final function ASPlayHelperSound();
native final function ASPauseHelperSound();

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
