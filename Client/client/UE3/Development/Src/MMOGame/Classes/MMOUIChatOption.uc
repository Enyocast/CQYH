class MMOUIChatOption extends MMOUIBase
	native(UI);

var array<GFxObject> ChannelList; 
var GfxObject ChannelNameInput;
var array<GFxObject> FilterList;

const MaxChatChannelNum = 6;
const MaxChatFilterNum = 8;

var int CurrentChannel;
var array<string> ChatChannelStr;

//event InitOnce()
//{	
//	local int i ;

//	super.InitOnce();
//	ChannelList.Add(MaxChatChannelNum);

//	for( i = 0 ; i < MaxChatChannelNum ; i++ )
//	{
//		ChannelList[i] = GetObject("btnChannelText"$i);
//	}

//	FilterList.Add(MaxChatFilterNum);

//	for( i = 0 ; i < MaxChatFilterNum ; i++ )
//	{
//		FilterList[i] = GetObject("ChatFilter"$i);
//	}

//	ChannelNameInput = GetObject("channelNameInput");
//	CurrentChannel = 0;
//}

//native function NativeInitOnce();


native function UpdateChannelButton();

native function ChannelNameChanged( string newName );
native function ClickChannel( int index );
native function ClickFilter( int id , bool sel );
native function ClickReset();
native function ClickApply();
native function ClickAddChannel();
native function ClickDelChannel();

//native function NativeOnShow(bool v);

// function UnitWidget()
// {
// 	Show(DefaultVisible);
// }

//--------------moved----------------
native function ASChatClickChatOption();
function ASChatOptionDeleteChannel()
{
	ClickDelChannel();
}

function ASChatOptionAddChannel()
{
	ClickAddChannel();
}

function ASChatOptionChannelNameChanged( string newName )
{
	ChannelNameChanged(newName);
}

function ASChatOptionClickChannel( int index )
{
	ClickChannel( index );
}

//function ASChatOptionClickFilter( int id , bool sel )
//{
	//ClickFilter( id , sel );
//}

function ASChatOptionReset()
{
	ClickReset();
}

function ASChatOptionApply()
{
	ClickApply();
}
DefaultProperties
{
	CanMoveTop=false
}
