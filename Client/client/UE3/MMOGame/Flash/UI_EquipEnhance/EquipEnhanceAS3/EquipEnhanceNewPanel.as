package UI_EquipEnhance.EquipEnhanceAS3
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
	import flash.geom.Matrix;
	import flash.geom.Point;
	import flash.display.Sprite;
	import flash.display.Bitmap;
	import flash.display.DisplayObject;
	import flash.display.Shape;
	import flash.utils.getDefinitionByName;
	import flash.filters.BevelFilter;
	import ActionScript3.Common.Utils.StyleType;
	import flash.filters.DropShadowFilter;

	public class EquipEnhanceNewPanel extends MyPanel
	{
		public var equipSlot_lv:TextField;
		public var equipSlot_name:TextField;
		
		public var equipSlot_curAttr1:TextField;
		public var equipSlot_curAttr2:TextField;
		//public var equipSlot_curAttr3:TextField;
		
		public var equipSlot_curValue1:TextField;
		public var equipSlot_curValue2:TextField;
		//public var equipSlot_curValue3:TextField;
		public var equipSlot_Dec:TextField;
		public var equipSlot_nxtAttr1:TextField;
		public var equipSlot_nxtAttr2:TextField;
		//public var equipSlot_nxtAttr3:TextField;
		
		public var equipSlot_nxtValue1:TextField;
		public var equipSlot_nxtValue2:TextField;
		//public var equipSlot_nxtValue3:TextField;
		public var needTips:EnhanceTips;
		
		public var btn_enhance:Button;
		
		public var TotalPropMc:MovieClip;
		
		//public var MoneyIcon_Large:MovieClip;
		//public var MoneyIcon_Small:MovieClip;
		//public var cost_mc0:TextField;
		//public var cost_mc1:TextField;
		public var CostMngTf:TextField;
		
/*		public var HintText_0:TextField;
		public var HintText_1:TextField;*/
		
		public var LevelLimitHint:TextField;
		
		public var MoneyDescText:TextField;
		public var tl_Success:TextField;
		public var SuccessRateTf:TextField;
		public var MatConsume_mc_0:MyItemSlot;
		public var itemLevel:MovieClip;
		public var itemLevel1:MovieClip;
		public var equipSlot_desc:TextField;
		public var slotLevel_cur:TextField;

		var itemSlot;Array;
		//var itemIcon:Array;
		var itemSlotLevel:Array;
		var enSlot:Array;
		//var selectIcon:Array;

		const slotNum:int = 15;
		
		var curSelect:int = -1;
		public var _over:MovieClip;
		public var lastSelect:MovieClip;//上一次选中
		public var iconover:MovieClip;//悬停
		public var light:MovieClip;//发光
		private var sp:MovieClip;
		public var bevel:BevelFilter= StyleType.getInstance().getBevel();
		public var shade:DropShadowFilter=StyleType.getInstance().getDropShadow();
        private var rotationArr:Array=[179,-51,-75,-102,102,51,-128,128,0,0,-25,154,76,-154,26];
		private var rotationP:Array=[new Point(223,334),new Point(134,150),new Point(112,194),new Point(112,246),new Point(332,243),new Point(308,149),new Point(134,292),new Point(311,290),new Point(220,109),new Point(),new Point(173,120),new Point(272,322),new Point(331,193),new Point(174,323),new Point(270,120)];
		override protected function configUI():void
		{
			
			itemSlot = [];
			itemSlotLevel =[];
			enSlot=[];
			super.configUI();
			sp=new MovieClip();
			sp.x=462;
			sp.y=45;
			this.addChild(sp);
			light.mouseChildren=false;
			light.mouseEnabled=false;
		    itemLevel.gotoAndStop(4); 
			itemLevel1.gotoAndStop(4);
			_over.visible=false;
			
			if(btn_enhance)
				btn_enhance.addEventListener( ButtonEvent.CLICK, ClickEnhance );
			//
			if(TotalPropMc)
			{
				TotalPropMc.addEventListener( MouseEvent.MOUSE_OVER, onHoverTotalEnhanceProp );
				TotalPropMc.addEventListener( MouseEvent.MOUSE_OUT, onMouseOutTotalEnhanceProp );
			}
			var i:int = 0;
			var slotMc:MovieClip;
			var levelMc:MovieClip;
            var enMc:MovieClip;
			for (i = 0; i < slotNum; i++)
			{
				if(i==9){
					itemSlot.push(null);
					itemSlotLevel.push(null);
					enSlot.push(null);
					continue;
				}
				slotMc = getChildByName( "itemSlot_" + i ) as MovieClip;
				slotMc.gotoAndStop(1);
				levelMc = getChildByName( "slotLevel_" + i ) as MovieClip;
				levelMc.gotoAndStop(6);
				enMc=getChildByName("en_"+i) as MovieClip;
				enMc.gotoAndStop(4);
				enMc.mouseChildren=false;
				enMc.mouseEnabled=false;
				enSlot.push(enMc);
				
				var shape:Shape=new Shape();
				shape.graphics.beginFill(0xffffff,0);
				shape.graphics.drawCircle(20,20,25);
				shape.graphics.endFill();
				slotMc.addChildAt(shape,0);
				if(i==0){
					setSelect(0,slotMc);
					this.createItemData(0);
				}
					itemSlot.push(slotMc);
					slotMc.addEventListener( MouseEvent.CLICK, ClickEquipSlot );
					slotMc.addEventListener(MouseEvent.ROLL_OVER,overHandler);
					slotMc.addEventListener(MouseEvent.ROLL_OUT,outHandler);
					levelMc.mouseEnabled = false;
					levelMc.mouseChildren = false;
					itemSlotLevel.push(levelMc);
			}
			//test2();
			
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
		
		function test1()
		{
			var dt:EquipSlotPropertyData = new EquipSlotPropertyData();
			dt.EquipEnhanceProperty0_0 = "力量+1";
			dt.EquipSlotName = "longhu";
			dt.LevelDesc = "luj";
			dt.EnhanceDesc = "hehe";
			dt.IconPath = "djdj";
			dt.Quality = 5;
			UpdateDetailPanel(dt);
						
		}
		
		function test2()
		{
			var dt:EquipSlotIconData = new EquipSlotIconData ;
			var ary:Array = new Array ;
			for(var i:int = 0; i < 15; ++i)
			{
				var udt:UIEquipSlotData = new UIEquipSlotData ;
				udt.level = 10;
				udt.iconPath = "";
				udt.select = false;
				udt.shotDesc = i+".test";
				
				ary.push(udt);
			}
			
			dt.EquipSlotDataArray = ary;
			UpdateSummaryPanel(dt);
		}

		public function ClickEnhance()
		{
			ExternalInterface.call( "ASEnhanceEquipSlot" );
		}

		public function ClickEquipSlot( e:MouseEvent ):void
		{
			if (e.target )
			{
				var mc:MovieClip=e.target as MovieClip;
				var id:int = itemSlot.indexOf(mc);
				setSelect(id,mc);
				_over.visible=false;
				createItemData(id);
				//setItemData(shape);
				if(id >= 0)
				{
					ExternalInterface.call( "ASSelectEquipSlot", id );
				}
			}
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
		

		public function ShowEquipSlotTips( e:MouseEvent ):void
		{
			if (e.target)
			{
				//var id:int = e.target.slotId_uc as int;
				var id:int = itemSlot.indexOf(e.target);
				if(id >= 0)
				{
					ExternalInterface.call( "ASShowTips_EquipSlot", id );
					//selectIcon[id].visible = true;
				}
			}
		}

		public function HideEquipSlotTips( e:MouseEvent ):void
		{
			if (e.target)
			{
				var id:int = itemSlot.indexOf(e.target);
				//var id:int = 0;
				ExternalInterface.call( "ASHideTips_EquipSlot", id );
				
				/*if(id != curSelect)
				{
					selectIcon[id].visible = false;
				}*/
			}
		}
		
		public function UpdateSummaryPanel( tData:Object )
		{
			var equipSlotIconData:EquipSlotIconData = tData as EquipSlotIconData;
			if ( equipSlotIconData )
			{
				var slotDataArray:Array = equipSlotIconData.EquipSlotDataArray;
/*				if(HintText_0)
				{
					HintText_0.text = equipSlotIconData.EnhanceHint_0;
				}
				if(HintText_1)
				{
					HintText_1.text = equipSlotIconData.EnhanceHint_1;
					HintText_1.visible=false;
				}*/
				
				
				for(var i:int = 0; i < slotDataArray.length; ++i)
				{
					var UIData:UIEquipSlotData = slotDataArray[i] as UIEquipSlotData;
					
					if(UIData.select)
					{
						var mc:MovieClip=itemSlot[i];
						if(mc != null)
						{
							this.setSelect(i,mc);
							this.createItemData(i);
						}
					}
					if( itemSlotLevel[i] != null )
					{
						if(UIData.level==0){
							(itemSlotLevel[i] as MovieClip).gotoAndStop(6);
						}else{
							(itemSlotLevel[i] as MovieClip).gotoAndStop(UIData.quality+1);
						}
					}
					if( enSlot[i] != null )
					{
						if(UIData.level==0){
							(enSlot[i] as MovieClip).gotoAndStop(4);
						}else{
							(enSlot[i] as MovieClip).gotoAndStop(UIData.EnhcClass+1);
						}
					}
				}
				
			}
		}

		public function UpdateDetailPanel( tData:Object )
		{
			if ( tData is EquipSlotPropertyData )
			{
				var equipSlotData:EquipSlotPropertyData = tData as EquipSlotPropertyData;

				if(equipSlot_desc)
				{
					setTxt(equipSlotData.Quality,equipSlotData.LevelDesc);
					//equipSlot_desc.text = equipSlotData.LevelDesc;
				}
								
				if(slotLevel_cur)
				{
					if(equipSlotData.LevelDesc.length==0){
						itemLevel.gotoAndStop(6);
					}else
					{
						itemLevel.gotoAndStop(equipSlotData.Quality+1);
					}
					if(equipSlotData.LevelDesc.length==0){
						itemLevel1.gotoAndStop(4);
					}else{
						itemLevel1.gotoAndStop(equipSlotData.EnhcClass+1);
					}
					if(equipSlotData.CurLevel>0){
						slotLevel_cur.text = equipSlotData.CurLevel+"级";
					}else{
						slotLevel_cur.text ="";
					}
                    
				}

				//根据品质设定颜色
				if(equipSlot_name)
				{
					equipSlot_name.text = equipSlotData.EquipSlotName;
				}				
				
				
				//equipSlot_curAttr.text = equipSlotData.GetCurrentDesc();
				if(equipSlotData.EquipEnhanceEffect_0_0 != null && equipSlotData.EquipEnhanceEffect_0_0 != "")
				{
					equipSlot_curAttr1.text = equipSlotData.EquipEnhanceProperty0_0;
					equipSlot_curValue1.text = "+ " + equipSlotData.EquipEnhanceEffect_0_0;
				}
				else
				{
					equipSlot_curAttr1.text = "";
					equipSlot_curValue1.text = "";
				}
				
				
				if(equipSlotData.EquipEnhanceEffect_0_1 != null && equipSlotData.EquipEnhanceEffect_0_1 != "")
				{
					equipSlot_curAttr2.text = equipSlotData.EquipEnhanceProperty0_1;
					equipSlot_curValue2.text = "+ " + equipSlotData.EquipEnhanceEffect_0_1;
				}
				else
				{
					equipSlot_curAttr2.text = "";
					equipSlot_curValue2.text = "";
				}
/*				if(equipSlotData.EquipEnhanceEffect_0_2 != null && equipSlotData.EquipEnhanceEffect_0_2 != "")
				{
					equipSlot_curAttr3.text = equipSlotData.EquipEnhanceProperty0_2;
					equipSlot_curValue3.text = "+ " + equipSlotData.EquipEnhanceEffect_0_2;
				}
				else
				{
					equipSlot_curAttr3.text = "";
					equipSlot_curValue3.text = "";
				}*/
				equipSlot_Dec.text=equipSlotData.NextEnhcLevelHint;
				if(equipSlotData.EquipEnhanceEffect_1_0 != null && equipSlotData.EquipEnhanceEffect_1_0 != "")
				{
					equipSlot_nxtAttr1.text = equipSlotData.EquipEnhanceProperty1_0;
					equipSlot_nxtValue1.text = "+ " + equipSlotData.EquipEnhanceEffect_1_0;
				}
				else
				{
					equipSlot_nxtAttr1.text = "";
					equipSlot_nxtValue1.text = "";
				}
				
								
				if(equipSlotData.EquipEnhanceEffect_1_1 != null && equipSlotData.EquipEnhanceEffect_1_1 != "")
				{
					equipSlot_nxtAttr2.text = equipSlotData.EquipEnhanceProperty1_1;
					equipSlot_nxtValue2.text = "+ " + equipSlotData.EquipEnhanceEffect_1_1;
				}
				else
				{
					equipSlot_nxtAttr2.text = "";
					equipSlot_nxtValue2.text = "";
				}
				
/*				if(equipSlotData.EquipEnhanceEffect_1_2 != null && equipSlotData.EquipEnhanceEffect_1_2 != "")
				{
					equipSlot_nxtAttr3.text = equipSlotData.EquipEnhanceProperty1_2;
					equipSlot_nxtValue3.text = "+ " + equipSlotData.EquipEnhanceEffect_1_2;
				}
				else
				{
					equipSlot_nxtAttr3.text = "";
					equipSlot_nxtValue3.text = "";
				}*/
				
				if(equipSlotData.EquipEnhanceEffect_0_0 != equipSlotData.EquipEnhanceEffect_1_0)
				{
					equipSlot_nxtValue1.textColor = 0x84ec60;
				}
				else
				{
					equipSlot_nxtValue1.textColor = 0x9d9d9d;
				}
				
				if(equipSlotData.EquipEnhanceEffect_0_1 != equipSlotData.EquipEnhanceEffect_1_1)
				{
					equipSlot_nxtValue2.textColor = 0x84ec60;
				}
				else
				{
					equipSlot_nxtValue2.textColor = 0x9d9d9d;
				}
				//Selection_mc.IconLoader_mc.source = "img://"+ equipSlotData.IconPath;
				if( equipSlotData.CanEnhance )
				{
					btn_enhance.enabled = true;
					CostMngTf.htmlText = equipSlotData.MoneyCostHtml;
					tl_Success.visible=true;
					SuccessRateTf.visible=true;
					LevelLimitHint.visible = false;
				}
				else
				{
					btn_enhance.enabled = false;
					CostMngTf.htmlText = equipSlotData.MoneyCostHtml;
					tl_Success.visible=false;
					LevelLimitHint.text = equipSlotData.EnhanceDesc;
					LevelLimitHint.visible = true;
					SuccessRateTf.visible=false;
				}
				
				//MoneyDescText.text = equipSlotData.MoneyDescText;

			}
			else
			{
				trace( "UpdateDetailPanel error: tData is not a instance of EquipSlotPropertyData" );
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