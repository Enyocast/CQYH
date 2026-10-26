class MMOGFXPlayer_FBEnter extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIFBEnter _FBEnter;
var MMOUIFBEnterMsg _FBEnterMsg;

//native function PostAdvance(float DeltaTime);

function RegisterFBEnter( MMOUIFBEnter mc )
{
	_FBEnter = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_FBEnter_FBEnter);
}

function RegisterFBEnterMsg( MMOUIFBEnterMsg mc )
{
	_FBEnterMsg = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_FBEnter_FBEnterMsg);
}
// event UnRegister()
// {
// 	super.UnRegister();
// 	RegisterUI( none, class'MMOUIManager'.default.Panel_FBEnter_FBEnter);
// 	RegisterUI( none, class'MMOUIManager'.default.Panel_FBEnter_FBEnterMsg);
// 	MMOUI::RegisterMoviePlayer(class'MMOUIManager'.default.MoviePlayer_FBEnter);
// 
// 	//class'MMOUIManager'.static.SetToggleFBEnterDelegate( none );
// 
// }

//
//function ToggleFBEnter()
//{
//	if( !_FBEnter.IsVisible ){
//		_FBEnter.NativeShow( true );
//	}
//	else{
//		_FBEnter.NativeShow( false );
//	}
//}
//
function UCEnterMap()
{
	_FBEnter.EnterMap();
}
//
function UCMapDiffChange( int Level )
{
	_FBEnter.MapDiffChange( Level );
}
//
function UCFBBranchChange( int iBranchIdx )
{
	_FBEnter.BranchChange( iBranchIdx );
}
//end of master enter
//
function UCPrepareEnter()
{
	_FBEnterMsg.PrepareEnter();
}
//
function UCCancelPrepare()
{
	_FBEnterMsg.CancelPrepare();
}
//end
//
DefaultProperties
{
	MovieInfoStr="UI_FBEnter.FBEnter"
	Priority=5
}
