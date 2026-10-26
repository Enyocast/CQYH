package ActionScript3.PlayerInfoWidget
{
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import ActionScript3.ItemSlot.MyItemSlotComponentIcon;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.MyTipButton;
	import ActionScript3.MyItemSlotShow;
	import ActionScript3.MyIconConponent;
	import UI_EquipEnhance.EquipEnhanceAS3.EquipSlotPropertyData;
	import UI_EquipEnhance.EquipEnhanceAS3.EquipSlotIconData;
	import UI_EquipEnhance.EquipEnhanceAS3.UIEquipSlotData;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.clik.events.ButtonEvent;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import ActionScript3.MyWindowsFrame;
	import flash.display.Shape;
	import flash.utils.getDefinitionByName;
	import flash.filters.BevelFilter;
	import ActionScript3.Common.Utils.StyleType;
	import flash.filters.DropShadowFilter;
	import flash.geom.Point;

	public class EnhanceViewPanel extends UIComponent
	{
		public var TotalPropMc:MovieClip;
	    public var equipSlot_desc:TextField;
		//public var equipSlot_name:TextField;
		public var slotLevel_cur:TextField;
		var itemSlot;Array;
		var itemSlotLevel:Array;
		var ColorArray:Array;

		const slotNum:int = 15;
        public var itemLevel:MovieClip;
		public var _over:MovieClip;
		public var lastSelect:MovieClip;//上一次选中
		public var iconover:MovieClip;//悬停
		public var light:MovieClip;//发光
		private var sp:MovieClip;
		public var bevel:BevelFilter= StyleType.getInstance().getBevel();
		public var shade:DropShadowFilter=StyleType.getInstance().getDropShadow();
        private var rotationArr:Array=[179,-51,-75,-102,102,51,-128,128,0,0,-25,154,76,-154,26];
		private var rotationP:Array=[new  Point(223,334),new Point(134,150),new Point(112,194),new Point(112,246),new Point(332,243),new Point(308,149),new Point(134,292),new Point(311,290),new Point(220,109),new Point(),new Point(173,120),new Point(272,322),new Point(331,193),new Point(174,323),new Point(270,120)];
		private var slotDataArray:Array;
		override protected function configUI():void
		{
			itemSlot = new Array  ;
			itemSlotLevel = new Array  ;
			sp=new MovieClip();
			sp.x=462;
			sp.y=45;
			this.addChild(sp);
            itemLevel.gotoAndStop(4);  
			super.configUI();

			ColorArray = new Array ;
			ColorArray.push(0x1eff00);
			ColorArray.push(0x71d5ff);
			ColorArray.push(0xa335ee);
			ColorArray.push(0xff8000);
			ColorArray.push(0xff0000);
			ColorArray.push(0xff8000);
			
			//
			if(TotalPropMc)
			{
				TotalPropMc.addEventListener( MouseEvent.MOUSE_OVER, onHoverTotalEnhanceProp );
				TotalPropMc.addEventListener( MouseEvent.MOUSE_OUT, onMouseOutTotalEnhanceProp );
			}

			var i:int = 0;
			var slotMc:MovieClip;
			var levelMc:MovieClip;

			for (i = 0; i < slotNum; i++)
			{
				if(i==9){
					itemSlot.push(null);
					itemSlotLevel.push(null);
					continue;
				}
				slotMc = getChildByName( "itemSlot_" + i ) as MovieClip;
				slotMc.gotoAndStop(1);
				levelMc = getChildByName( "slotLevel_" + i ) as MovieClip;
				levelMc.mouseEnabled = false;
				levelMc.mouseChildren = false;
				levelMc.gotoAndStop(4);
				slotMc.addEventListener( MouseEvent.CLICK, ClickEquipSlot );
				slotMc.addEventListener(MouseEvent.ROLL_OVER,overHandler);
				slotMc.addEventListener(MouseEvent.ROLL_OUT,outHandler);
				var shape:Shape=new Shape();
				shape.graphics.beginFill(0xffffff,0);
				shape.graphics.drawCircle(20,20,25);
				shape.graphics.endFill();
				slotMc.addChildAt(shape,0);
				itemSlot.push(slotMc);
				itemSlotLevel.push(levelMc);
				if(i==0){
					setSelect(0,slotMc);
					this.createItemData(0);
				}

			}
			test2();
		}
		
		public function ClickEquipSlot( e:MouseEvent ):void
		{
			if (e.target )
			{
				var mc:MovieClip=e.target as MovieClip;
				var id:int = itemSlot.indexOf(mc);
                var UIData:UIEquipSlotData = slotDataArray[id] as UIEquipSlotData;
				equipSlot_desc.text=UIData.shotDesc;
				slotLevel_cur.text=UIData.level.toString();
				setSelect(id,mc);
				_over.visible=false;
				createItemData(id);
				//setItemData(shape);
			}
		}
		
		private function overHandler(e:MouseEvent):void
		{
			if (e.target )
			{
				var mc:MovieClip=e.target as MovieClip;
				if(this.lastSelect==mc){
					return;
				}
				_over.visible=true;
				_over.x=mc.x-20;
				_over.y=mc.y-20;
			}
		}
		
		private function outHandler(e:MouseEvent):void
		{
			_over.visible=false;
		}
		
		private function setSelect(id:int,mc:MovieClip):void
		{
				if(this.lastSelect!=null){
					this.lastSelect.gotoAndStop(1);
				}
				mc.gotoAndStop(2);
				light.x=rotationP[id].x;
				light.y=rotationP[id].y;
				light.rotation=rotationArr[id];
				iconover.x=mc.x-20;
			    iconover.y=mc.y-20;
				this.lastSelect=mc;
		}
		
		private function createItemData(id:int):void
		{
			if(id==12){
				id=11;
			}
			if(id==14){
				id=13;
			}
			if(sp.numChildren>0){
				sp.removeChildAt(0);
			}
			var mc:MovieClip=new (getDefinitionByName("itemSlot"+id) as Class);
			if(mc){
				mc.gotoAndStop(1);
				sp.addChild(mc);
			}
		}
		

		function test2()
		{
			var dt:EquipSlotIconData = new EquipSlotIconData ;
			var ary:Array = new Array ;
			for(var i:int = 0; i < 15; ++i)
			{
				var udt:UIEquipSlotData = new UIEquipSlotData ;
				udt.level = i;
				udt.iconPath = "";
				udt.select = false;
				udt.shotDesc = i+".test";
				
				ary.push(udt);
			}
			
			dt.EquipSlotDataArray = ary;
			UpdateSummaryPanel(dt);
		}
		
		public function UpdateSummaryPanel( tData:Object )
		{
			var equipSlotIconData:EquipSlotIconData = tData as EquipSlotIconData;
			if ( equipSlotIconData )
			{
				slotDataArray= equipSlotIconData.EquipSlotDataArray;
				
				for(var i:int = 0; i < slotDataArray.length; ++i)
				{
					var UIData:UIEquipSlotData = slotDataArray[i] as UIEquipSlotData;
					
					if(i==0)
					{
							equipSlot_desc.text=UIData.shotDesc;
							slotLevel_cur.text=UIData.quality+"";
					}
					if( itemSlotLevel[i] != null )
					{
						if(UIData.level==0){
							(itemSlotLevel[i] as MovieClip).gotoAndStop(4);
						}else{
							(itemSlotLevel[i] as MovieClip).gotoAndStop(UIData.EnhcClass+1);
						}
					}
				}
				
			}
		}
		
		public function setTxt(ColorName:int,ItemName:String):void
		{
			equipSlot_desc.filters=null;
			switch(ColorName)
			{
				case 0:
				{
					//tF_ItemName.textColor=0x84ec60;
					bevel.shadowColor=0x84ec60;
					bevel.highlightColor=0xa6ed8d;
					break;
				}
				case 1:
				{
					//tF_ItemName.textColor=0x399bff;
					bevel.shadowColor=0x399bff;
					bevel.highlightColor=0x63b0fe;
					break;
				}
				case 2:
				{
					//tF_ItemName.textColor=0xc43cfc;
					bevel.shadowColor=0xc43cfc;
					bevel.highlightColor=0xcb6af3;
					break;
				}
				case 3:
				{
					//tF_ItemName.textColor=0xf9a410;
					bevel.shadowColor=0xf9a410;
					bevel.highlightColor=0xf9b43c;
					break;
				}
				default:
				{
					bevel.shadowColor=0xf99272;
					bevel.highlightColor=0xf64e1a;
					break;
				}
			}
			equipSlot_desc.textColor=0xffffff;
			equipSlot_desc.text = ItemName;
			shade.blurX=shade.blurY=2;
			shade.distance=1;
			equipSlot_desc.filters=[shade,bevel];
		}

		//
		public function onHoverTotalEnhanceProp( e:Event )
		{
			ExternalInterface.call( "ASShowTotalEnhancProp" );
		}
		
		//
		public function onMouseOutTotalEnhanceProp( e:Event )
		{
			ExternalInterface.call( "ASHideTotalEnhancProp" );
		}
	}
}