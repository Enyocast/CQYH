class MMOUIQuestRewardBuyTimesPanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
// 还能购买的剩余次数
event CallUpdateRewardQuestBuyLeftTimes(int times)
{
	ActionScriptVoid("UCUpdateRewardQuestBuyLeftTimes");
}

event CallUpdateRewardQuestBuyTimesConsume(string consume)
{
	ActionScriptVoid("UCUpdateRewardQuestBuyTimesConsume");
}

native final function ASUpdateRewardQuestBuyTimes(int times);
native final function ASBuyTimes(int times);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
	IsTargetOutDistanceClose = true
}
