package ActionScript3.Friend
{

	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;

	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.core.UIComponent;
	import flash.display.MovieClip;

	import scaleform.clik.controls.TextInput;
	import scaleform.clik.controls.RadioButton;
	import ActionScript3.MyScrollBar;
	import scaleform.clik.controls.ButtonBar;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ButtonBarEvent;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.utils.getDefinitionByName;
	import flash.text.TextField;
	import scaleform.gfx.Extensions;
	import scaleform.gfx.MouseEventEx;
	import flash.display.Sprite;
	import ActionScript3.MyScrollPanel;
	import flash.geom.Point;
	import ActionScript3.MyActivePanel;
	import flash.events.FocusEvent;
	import flash.events.TextEvent;
	import scaleform.clik.controls.UILoader;
	import ActionScript3.Common.Utils.StyleType;

	//
	public class ContactListStatic
	{
		static public var OFFLINE:int = 0;//离线
		static public var ONLINE:int = 1;//在线
		static public var BUSY:int = 2;//忙碌 
	    static public var AFK:int = 3;//离开
		static public var MaxGroup:int = 11;
		
		static public var frameBg:Object = {x:7,y:105,width:210,height:344};

		static public function SetItemValue( item:Button , Playername:String , Lv:int , Carrer:String , Location:String,Sign:String , RoleId:int , Status:int , headIconPath:String="" )
		{
			if (item)
			{
				var NameText:TextField = item.getChildByName("tF_playerName") as TextField;
				NameText.text = Playername;

				var LocText:TextField = item.getChildByName("tF_playerLocation") as TextField;
				LocText.text = Location;
				LocText.visible=false;
				var LvText:TextField = item.getChildByName("tF_playerLv") as TextField;
				LvText.text = String(Lv);
                LvText.visible=false;
				var CarrerText:TextField = item.getChildByName("tF_playerCarrer") as TextField;
				CarrerText.text = Carrer;
				CarrerText.visible=false;
				var SignText:TextField = item.getChildByName("tF_playerSignature") as TextField;
				SignText.text = Sign;

				var ContactStatus:MovieClip = item.getChildByName("ContactStatus") as MovieClip;
				ContactStatus.gotoAndStop(Status+1);
				if(Status==3)
				{
					NameText.textColor=0x9d9d9d;
				}
				else
				{
					NameText.textColor=0xffffff;
				}
				var headIcon:UILoader = item.getChildByName("HeadIcon") as UILoader;
				if (headIcon)
				{
					headIcon.source = headIconPath;
				}
				item.iteminfoid = RoleId;

			}
		}
	}
}