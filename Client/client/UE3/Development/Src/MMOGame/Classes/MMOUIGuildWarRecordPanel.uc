class MMOUIGuildWarRecordPanel extends MMOUIBase
	native(UI);

var int _CurPageIndex;
var int _CurPageType;
var bool _LockPage;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallUpdateGuildWarRecordList(GFxObject dataProvider)
{
	ActionScriptVoid("UpdateGiildWarRecordData");
}

event CallUpdateGuildWarRecordPage(int totalPage, int curPage)
{
	ActionScriptVoid("UpdateGiildWarRecordPageText");
}

native final function ASPrevRecordPageClick();
native final function ASNextRecordPageClick();

DefaultProperties
{
	_CurPageIndex=0
	_CurPageType=0
	_LockPage=false
	IsDynamicLoad=true
	DefaultVisible=false
}
