package UI_LoginWidget.AS3 {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.getDefinitionByName;
	
	import UI_LoginWidget.AS3.RoleInfoData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ComponentEvent;
	import flash.text.TextFormat;
	
	public class RoleListBtn extends MovieClip {
		
		public var tF_Name:TextField;
		public var tF_Level:TextField;
		public var tF_Profession:TextField;
        public var mc_head:BaseSelectBtn;
		public var format:TextFormat;
		public var tF_Guild:TextField;
		public function RoleListBtn():void
		{
			tF_Name.mouseEnabled=false;
			tF_Level.mouseEnabled=false;
			tF_Profession.mouseEnabled=false;
			tF_Guild.mouseEnabled=false;
			tF_Guild.visible = false;
			format=tF_Name.defaultTextFormat;
			mc_head=new (getDefinitionByName("Profession00") as Class);
			this.addChildAt(mc_head,0);
		}

		public function SetRoleBtn( roleData:RoleInfoData ):void
		{
			if ( null != roleData && roleData.HasRole )
			{
				if(mc_head){
				    mc_head.removeEventListener(MouseEvent.DOUBLE_CLICK,DoubleClick);
					this.removeChild(mc_head);
				}
				visible = true;
				tF_Name.text = roleData.RoleName;
				tF_Level.text = roleData.Level;
				tF_Profession.text=roleData.CareerName;
				tF_Guild.text = roleData.GuildName;
				mc_head=new (getDefinitionByName("Profession"+roleData.Sex+""+roleData.Career) as Class);
                //mc_head.show(roleData.OverTime);
				mc_head.doubleClickEnabled = true;
			    mc_head.addEventListener(MouseEvent.DOUBLE_CLICK,DoubleClick);
				this.addChildAt(mc_head,0);
			}
			else
			{
				visible = false;
				tF_Name.text = "";
				tF_Level.text = "";
				tF_Profession.text = "";
				//mc_Head.visible = false;
			}
		}
		
		public function update(b:Boolean):void
		{
			if(b==true){
				format.color=0xffffff;
				tF_Name.setTextFormat(format);
				format.color=0x93dafe;
				tF_Level.setTextFormat(format);
				tF_Profession.setTextFormat(format);
				tF_Guild.setTextFormat(format);
			}else{
			    format.color=0xd1c09e;
				tF_Name.setTextFormat(format);
				format.color=0x78A4BA;
				tF_Level.setTextFormat(format);
				tF_Profession.setTextFormat(format);
				tF_Guild.setTextFormat(format);
			}
		
		}
		
		public function DoubleClick(evt:MouseEvent):void
		{
			ExternalInterface.call("DirectSelectRole",evt.target.itemid  );
		}
			
	}
	
}
