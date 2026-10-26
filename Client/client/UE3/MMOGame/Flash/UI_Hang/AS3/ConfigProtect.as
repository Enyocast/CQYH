package UI_Hang.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.Button;
	import flash.external.ExternalInterface;
	
	
	public class ConfigProtect extends UIComponent {
		
		public var protect0:ProtectItem1;
		public var protect1:ProtectItem1;
		public var protect2:ProtectItem2;
		public var protect3:ProtectItem2;
		public var protect4:ProtectItem2;
		public var protect5:ProtectItem2;
		public var protect6:ProtectItem2;
		public var protect7:ProtectItem2;
		public var btn_apply:Button
		public var btn_confirm:Button;
		public var btn_cancel:Button;
		public var btn_default:Button;
		public var type:int;
		public const MaxLen:int=8;
		override protected function configUI():void
		{
			super.configUI();
			protect0.type=0;
			protect1.type=1;
			protect1.ProtectType=1;
			protect2.type=5;
			protect3.type=5;
			protect3.ProtectType=1;
			protect4.type=5;
			protect5.type=5;
			protect5.ProtectType=1;
			protect6.type=8;
			protect7.type=8;
			protect7.ProtectType=1;
			
			protect0.setCheckBoxTxt();
			protect1.setCheckBoxTxt(true);
			
			btn_apply.addEventListener(MouseEvent.CLICK,OnApply);
			btn_confirm.addEventListener(MouseEvent.CLICK,OnOK);
			btn_cancel.addEventListener(MouseEvent.CLICK,OnCancel);
			btn_default.addEventListener(MouseEvent.CLICK,OnDefault);
			if(1){
				this.testData();
			}
		}
		
		//请求读取 道具默认配置
		private function OnDefault(evt:MouseEvent):void
		{
			ExternalInterface.call("ASProtectConfiglData", this);
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
			var arr:Array=[];
			var dat:ProtectData;
			var i:int=0;
			for(i=0;i<MaxLen;i++)
			{
				var mc:BaseProtectItem=this.getChildByName("protect"+i) as BaseProtectItem;
				dat=mc.getProtectData();
				arr.push(dat);
			}
			ExternalInterface.call("ASApplyProtectConfig",arr);//请求保护配置
		}
		
		//设置保护数据
		public function SetProtectData(dat:Array):void
		{
			if(dat)
			{
				var i:int=0;
				var l:int=dat.length;
				for(i=0;i<MaxLen;i++)
				{
					var mc:BaseProtectItem=this.getChildByName("protect"+i) as BaseProtectItem;
					var obj:ProtectData=dat[i];
					if(mc && obj)
					{
						mc.updateData(obj);
					}
				}
			}
		}
		
		public function setItemData(dat:Array):void
		{//设置道具数据
		    if(dat)
			{
				var i:int=2;
				for(i=2;i<MaxLen;i++)
				{
					var mc:BaseProtectItem=this.getChildByName("protect"+i) as BaseProtectItem;
					if(mc)
					{
						type=mc.type;
						var arr:Array=dat.filter(noType);
						mc.updateMenuData(arr);
					}
				}
			}
		}
		
	    function noType(item:Object,index:int,arr:Array):Boolean
		{
			if(item.itemType==type)
			{
				return true;
			}
			return false;
		}
		
		public function SetMaxHMP(maxHp:int,maxMp:int):void
		{
			var i:int=0;
			for(i=0;i<MaxLen;i++)
			{
				var mc:BaseProtectItem=this.getChildByName("protect"+i) as BaseProtectItem;
				if(mc)
				{
					mc.updateTxt(maxHp,maxMp);
				}
			}
		}
		
		private function testData():void
		{
			var itemArr:Array=[];
			 for (var i:int = 0; i < 20; i++) {
				 var dat:ItemData=new ItemData();
				 dat.index=i;
				 dat.label="道具名称"+i;
				 if(i<6)
				 {
					 dat.itemType=1;
				 }
				 else if(i<14)
				 {
					 dat.itemType=2;
				 }
				 else
				 {
					 dat.itemType=3;
				 }
                 itemArr.push(dat);
            }
			setItemData(itemArr);
		}
		
		public function hide():void
		{
			var i:int=2;
			for(i=2;i<MaxLen;i++)
			{
				var mc:ProtectItem2=this.getChildByName("protect"+i) as ProtectItem2;
				mc.clear();
			}
			
		}
	}
	
}
