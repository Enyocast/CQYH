//
//在屏幕上显示较大的Hint
//
class MMOStatusProc_ShowSceneHint extends Object implements(IMMOStatusProc)
	native
	editinlinenew
	hidecategories(Object);


/*
 *历史博物馆，用例：
 * //阿门 Ugly代码
		//做一个UI通知的action @todo
		AMMOPlayerController* ctrl = MMOFacade::getSingleton().GetMainController();
		AMMOHud* hud = Cast<AMMOHud>(ctrl->myHUD);
		if( msg->wSpellID == 7010 )
		{
			hud->HudMovie->eventShowMsgSceneHint( ctrl->StringMap->eventGetGamePlayStrByName( "DoorOfFateOpen" ) );
		}
		else if( msg->wSpellID == 7021  )
		{
			hud->HudMovie->eventShowMsgSceneHint( ctrl->StringMap->eventGetGamePlayStrByName( "TransducerOpen" ) );
		}
 * */
//在Localization里的tGamePlay中定义
var() string StrId;

event OnExecute(MMOActor actor)
{
	//现在不用了
	//local MMOPlayerController pc;
	//pc = actor.GetMainController();
	
	//`log( "############################################MMOStatusProc_ShowSceneHint:"@StrId);
	//MMOHud(pc.myHUD).HudMovie.ShowMsgSceneHint( ParseLocalizedPropertyPath( "MMOGame.GamePlay." $ StrId ) );
	//NativeOnExecute(actor);
}
//native function NativeOnExecute(MMOActor actor);
native function Update(MMOActor actor);


defaultproperties
{

}