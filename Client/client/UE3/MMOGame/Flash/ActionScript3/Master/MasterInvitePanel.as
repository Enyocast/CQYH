package ActionScript3.Master {
	
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.UILoader;
	import flash.text.TextField;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import scaleform.clik.events.ComponentEvent;
	
	
	public class MasterInvitePanel extends MyPanel {
		
		public var tf_playerName:TextField;
		public var tf_level:TextField;
		public var tf_class:TextField;
		public var tf_num:TextField;
		
		public var btn_ok:Button;
		public var btn_no:Button;
		public var chk_tip:CheckBox;
		public var head_icon:UILoader;
		
		private var Id:int;
		override protected function configUI():void
		{
			this.ShowMode="BC";
			super.configUI();
			this.SetWindowTitle("收徒邀请");
			chk_tip.addEventListener(ButtonEvent.CLICK,clickHandler);
			btn_ok.addEventListener(MouseEvent.CLICK,okHandler);
			btn_no.addEventListener(MouseEvent.CLICK,closeHandler);
			this.addEventListener(ComponentEvent.HIDE,hideHandler);
			//UCUpdateHelloMasterInfo({RoleName:"deaa",Level:12,num:5});
			//UCUpdateHelloMasterName({RoleName:"222",Level:12,ClassName:"法师",num:5});
		}
		private function hideHandler(evt:Event):void
		{
			Id=0;
			tf_playerName.htmlText="";
		    tf_level.htmlText="";
			tf_class.htmlText="";
			tf_num.htmlText="";
			head_icon.visible=false;
		}
		private function clickHandler(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASMasterInviteCheckBox",chk_tip.selected);
		}
		
		private function okHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASMasterInviteSummit",Id);
		}
		
		private function closeHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASOnMasterInvitePanelClose" , Id);
		}
		
		public function UCSetCheckBox(bl:Boolean):void
		{
			chk_tip.selected=bl;
		}
		
		public function UCUpdateHelloMasterInfo(dat:Object):void
		{
			Id=dat.Id;
			//if(dat.RoleName is undefined)
			//{
				//tf_playerName.htmlText="<font color='#FFF79A'>姓名</font>   未知玩家";
			//}
			//else
			//{
				tf_playerName.htmlText="<font color='#FFF79A'>姓名</font>"+dat.RoleName;
			//}
			
		    tf_level.htmlText="<font color='#FFF79A'>等级</font>"+dat.Level.toString();
			tf_class.htmlText="<font color='#FFF79A'>职业</font>"+dat.ClassName;
			tf_num.htmlText="<font color='#FFF79A'>名师值</font>"+dat.num;
			head_icon.source=dat.HeadIcon;
			head_icon.visible=true;
		}
		
		public function UCUpdateHelloMasterName(dat:Object):void
		{
			tf_playerName.htmlText="<font color='#FFF79A'>姓名</font>"+dat.RoleName;
			tf_class.htmlText="<font color='#FFF79A'>职业</font>"+dat.ClassName;
			head_icon.source=dat.HeadIcon;
			head_icon.visible=true;
		}
	}
	
}
