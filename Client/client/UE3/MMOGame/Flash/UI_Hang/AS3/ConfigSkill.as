package UI_Hang.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.data.DataProvider;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import flash.events.Event;
	
	
	public class ConfigSkill extends UIComponent{
		
		public var warrior_0:CheckBox;
		public var warrior_1:CheckBox;
		public var warrior_2:CheckBox;
		public var warrior_3:CheckBox;
		public var master_0:CheckBox;
		public var taoist_0:CheckBox;
		public var chk_timer:CheckBox;
		public var dropMenu:DropdownMenu;
		public var txt_timer:TextInput;
		public var btn_apply:Button;
		public var btn_confirm:Button;
		public var btn_cancel:Button;
		public var btn_default:Button;
		override protected function configUI():void
		{
			super.configUI();
			btn_apply.addEventListener(MouseEvent.CLICK,OnApply);
			btn_confirm.addEventListener(MouseEvent.CLICK,OnOK);
			btn_cancel.addEventListener(MouseEvent.CLICK,OnCancel);
			btn_default.addEventListener(MouseEvent.CLICK,OnDefault);
			
			txt_timer.addEventListener(Event.CHANGE,timerHandler);
			txt_timer.textField.restrict="0-9";
			txt_timer.maxChars=3;
			if(0)
			{
				testData();
			}
		}
		
		private function timerHandler(evt:Event):void
		{
			var num:int=int(txt_timer.text);
			if(num>255)
			{
				txt_timer.text=255+"";
			}
		}
		
		public function setData(dat:SkillConfigData):void
		{
			warrior_0.selected=dat.warrior_0;
			warrior_1.selected=dat.warrior_1;
			warrior_2.selected=dat.warrior_2;
			warrior_3.selected=dat.warrior_3;
			master_0.selected=dat.master_0;
			taoist_0.selected=dat.taoist_0;
			chk_timer.selected=dat.autoTimer;
			txt_timer.text=dat.timer.toString();
			setMenuData(dat.skillArr,dat.skillId);
		}
		
		public function setMenuData(arr:Array,skillId:int=0):void
		{
			var l:int=arr.length;
			if(l>1){
				dropMenu.menuRowCount=3;
			}
			var dp:DataProvider=new DataProvider(arr);
			dropMenu.dataProvider=dp;
			dropMenu.invalidateData();
			dropMenu.validateNow();
			if(l>0)
			{
				var i:int=0;
				for(i=0;i<l;i++)
				{
					var object:Object=arr[i];
					if(skillId==0)
					{
						skillId=object.index;
						dropMenu.selectedIndex = 0;
						break;
					}
					if(object.index==skillId)
					{
						dropMenu.selectedIndex = i;
						break;//跳出循环
					}
				}
			}
		}
		
		//请求读取 道具默认配置
		private function OnDefault(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHangConfigSkillData", this);
		}
		private function OnOK(evt:MouseEvent):void
		{
			OnApply(null);
			OnCancel(null);	
		}
		private function OnCancel(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASOnPanelClose" , "Assist");
		}
		private function OnApply(evt:MouseEvent):void
		{
			var dat:SkillConfigData = new SkillConfigData();

			dat.warrior_0=warrior_0.selected;
			dat.warrior_1=warrior_1.selected;
			dat.warrior_2=warrior_2.selected;
			dat.warrior_3=warrior_3.selected;
			dat.master_0=master_0.selected;
			dat.taoist_0=taoist_0.selected;
			dat.autoTimer=chk_timer.selected;
			dat.timer=int(txt_timer.text);
			if(dat.timer<1)
			{
				txt_timer.text=1+"";
			}
			var itemArr:Array=dropMenu.dataProvider as Array;
			var i:int=dropMenu.selectedIndex;
			if(itemArr)
			{
				var obj:Object=itemArr[i];
				if(obj)
				{
					dat.skillId=obj.index;
				}
			}
			
			ExternalInterface.call("ASApplyHangSkillConfig",dat);//请求外挂道具配置
		}
		
		public function hide():void
		{
			dropMenu.close();
		}
		

		private function testData():void
		{
			var dat:SkillConfigData=new SkillConfigData();
			dat.warrior_0=true;
			dat.warrior_1=false;
			dat.warrior_2=true;
			dat.warrior_3=false;
			dat.master_0=true;
			dat.taoist_0=true;
			dat.autoTimer=true;
			dat.timer=4;
			dat.skillId=1;
            for (var i:int = 0; i < 8; i++) {
                dat.skillArr.push({label:"技能列表 " + i, index:3+i});
            }
			setData(dat);
			setMenuData(dat.skillArr,6);
		}
	}
	
}
