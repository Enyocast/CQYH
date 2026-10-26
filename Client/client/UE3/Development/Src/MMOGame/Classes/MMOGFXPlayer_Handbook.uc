class MMOGFXPlayer_Handbook extends MMOGFXPlayer
	native(UI);

var MMOUIHandbookPanel _HandbookPanel;
var TurnButtonStats _PlayerRotStates;
var TurnButtonStats _NpcRotStates;

event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

// AS->UC
function ASRegisterHandbookPanel(MMOUIHandbookPanel mc)
{ 
	_HandbookPanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_Handbook);
	
	self.OnPostAdvance = _HandbookPanel.CheckPendingRT;
}

native function ASSetHandbookClass(int handbookClass);
native function ASSetHandbookType(int selectIndex);
native function ASClickHandbookItem(int type, int index);
native function ASShowTips_SkillSettingActive( GFxObject mc );
native function ASHideTips_SkillSettingActive( GFxObject mc );

native function ASShowTips_MonsterSkill( GFxObject mc );
native function ASHideTips_MonsterSkill( GFxObject mc );

native function ASGotoMapPage(string mapName);
native function ASGotoMonsterPage(string monsterName);
native function ASCheckUseableOnly(bool useableOnly);
native function ASSearchByKey(string key);
native function ASBackButtonClick();

native function ASOpenWorldMap(int mapId);
native function ASGotoPosition(int mapId);
native function ASPlayDesciptionSound();

native function ASPlayerRotate(int dir);
native function ASNpcRotate(int dir);
native function ASReleaseRotate();
native function ASGotoEquipPage(int itemId);
native function PostAdvance(float deltaTime);

DefaultProperties
{
	MovieInfoStr="UI_Handbook.Handbook"
	Priority = 5
}
