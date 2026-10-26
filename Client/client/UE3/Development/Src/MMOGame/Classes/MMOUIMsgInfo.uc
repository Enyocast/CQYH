class MMOUIMsgInfo extends MMOUIBase
	native(UI)
	;

var const float AlphaDeltaValue; 
var const float ShowTime;
var const int MsgInfoItemNum;
var const float SameMsgCdTimeLimit;
var const float MsgDeltaTime;


enum MsgInfoItemType
{
	MsgInfoType_Warning,
	MsgInfoType_Normal,
	MsgInfoType_Table,
	MsgInfoType_Ex1,
	MsgInfoType_Num,
};

struct native MsgInfoItem
{
	var bool MsgShow;
	var init string MsgText;
	var float MsgAlpha;
	var int Type;
	var float deltaTime;
};

var array<MsgInfoItem> MsgInfoItemList;
var array<GFxObject> MsgInfoObjectList;
var array<string> MsgInfoTextColor;
var array<string> MsgInfoFilterColor;
var float MsgCdTime;
var string LastMsg;
var bool InCdTime;

event CallSetFilter( GFxObject data )
{
	ActionScriptVoid("SetFilter");
}

native final function AddMsgInfo( string Text, MsgInfoItemType type , string SndName, int idx );


native function UpdateMsgText();
native function TickWidget( float deltaTime);
native final function string TryGetString(string id_str);
native final function PlayMsgSound(string snd_name, int idx = -1);
native function PostAdvance(float DeltaTime );

native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

DefaultProperties
{
	AlphaDeltaValue=1
	MsgCdTime=0
	SameMsgCdTimeLimit=1.0
	MsgInfoItemNum=4
	DefaultVisible=true
	CloseOnEsc=false
	LastMsg=""
	InCdTime=false
}
