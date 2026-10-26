package ActionScript3
{
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.Common.Utils.StyleType;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	//import fl.transitions.easing.Strong;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ComponentEvent;
	import scaleform.clik.events.FocusHandlerEvent;
	import scaleform.clik.managers.FocusHandler;
	import scaleform.clik.managers.PopUpManager;
	//import scaleform.clik.motion.Tween;
	import scaleform.gfx.MouseEventEx;

	
	public class MyPanel extends UIComponent
	{
		[Inspectable(type = "String",name = "_ShowMode")]
		public var ShowMode:String = "";
		[Inspectable(type = "Number",name = "_SpecialWidth")]
		public var SpecialWidth:Number = 0;
		[Inspectable(type = "Number",name = "_SpecialHeight")]
		public var SpecialHeight:Number = 0;

		[Inspectable(type = "Number",name = "_TweenX")]
		public var TweenOffsetX:Number = 0;
		[Inspectable(type = "Number",name = "_TweenY")]
		public var TweenOffsetY:Number = 0;


		[Inspectable(type = "String",name = "Caption")]
		public var _caption:String = "";
				
		public var PanelName:String;
		protected var bDrag:Boolean = false;
		
		public var OrignW;
		public var OrignH;
		public var cavasWidth:int = 1280;
		public var cavasHeight:int = 720;
		
		public var InfoDragButton_mc:Button;
		public var btn_close:MyCloseButton;
		public var btn_help:MyHelperButton;

/*		public var TweenShow:Tween;
		public var TweenShowFlag:Boolean = false;*/
		public var MyWindowsFrame_mc:MyWindowsFrame;
		
		public var g_panelList:Array = [];
		
		protected var _displayPriority:int = 2;
		public var CurPriority:int=0;

		override protected function configUI():void
		{
			g_panelList.push(this); // 阻止被GC
			super.configUI();
			init();
		}
		
		private function init():void
		{
			OrignW = width;
			OrignH = height;
			if ( SpecialWidth != 0)
			{
				OrignW = SpecialWidth;
			}
			if ( SpecialHeight != 0)
			{
				OrignH = SpecialHeight;
			}
			configWindowsFrame();
			//add by wph@2015-10-16 set panel to top when visible set to be true;
			this.addEventListener(ComponentEvent.SHOW, onComponentEventShow);
		}
		
		protected function onWindowSwapToFront(e:MouseEvent):void 
		{
			if(parent)
			{
				var topIndex:int = parent.numChildren - 1;
				if(parent.getChildIndex(this) != topIndex)
				{
					parent.setChildIndex(this, topIndex);
				}
			}
        }
		
		private function onComponentEventShow(evt:Event):void
		{
			onWindowSwapToFront(null);
		}
		
		private function configWindowsFrame():void
		{
			if (MyWindowsFrame_mc)
			{
				InfoDragButton_mc = MyWindowsFrame_mc.InfoDragButton_mc;
				if(MyWindowsFrame_mc.btn_close){
					btn_close = MyWindowsFrame_mc.btn_close;
				    btn_close.CloseTargetPanel = this;
				}
				if(MyWindowsFrame_mc.btn_help){
					btn_help = MyWindowsFrame_mc.btn_help;
				    btn_help.HelperTargetPanel = this;
				}
				SetPanelDrag();
			}
			GameDispathcher.getInstance().addEventListener(ParamEvent.STAGECHANGE,stageChangeHandler);
			stageChangeHandler(null);
		}
		
		protected function stageChangeHandler(evt:ParamEvent):void
		{
			this.cavasWidth = root.stage.stageWidth;
			this.cavasHeight = root.stage.stageHeight;
			this.setCenter();
		}

		public function onRmoved(e:Event)
		{
			if (this.InfoDragButton_mc !=null)
			{
				InfoDragButton_mc.removeEventListener( MouseEvent.MOUSE_DOWN ,onWindowStartDrag );
			}
			this.removeEventListener(Event.REMOVED_FROM_STAGE, onRmoved );

			InfoDragButton_mc = null;
			btn_close = null;
			btn_help = null;
			//TweenShow = null;
			MyWindowsFrame_mc = null;
		}
        
		//设置窗口标题
		public function SetWindowTitle(value:String):void
		{
			if (MyWindowsFrame_mc && MyWindowsFrame_mc.tF_windowTitle)
			{
				MyWindowsFrame_mc.tF_windowTitle.text = value;
			}
		}

        //设置窗口帮组按钮是否可用
		public function ShowHelperButton(bShow:Boolean):void
		{
			if (MyWindowsFrame_mc && MyWindowsFrame_mc.btn_help)
			{
				MyWindowsFrame_mc.btn_help.enabled =bShow;
			}
		}
		
		public function SetFocusMc(elemName1:String,elemName2:String,elemName3:String,elemName4:String):void
		{//C++主动设置某个组件的焦点不再使用，以免冲突----by kxw
		    //目前C++调用只有2处地方，一个是创建公会，一个是好友签名处
/*			var obj;
			var objNextName:String;
			var obj1 = getChildByName(elemName1);
			if (obj1)
			{
				obj = obj1;
				objNextName = elemName2;
				if (elemName2.length > 0)
				{
					var obj2 = obj1.getChildByName(elemName2);
					if (obj2)
					{
						obj = obj2;
						objNextName = elemName3;
						if (elemName3.length > 0)
						{
							var obj3 = obj2.getChildByName(elemName3);
							if (obj3)
							{
								obj = obj3;
								objNextName = elemName4;
								if (elemName4.length > 0)
								{
									var obj4 = obj3.getChildByName(elemName4);
									if (obj4)
									{
										obj = obj4;
										objNextName = "";
									}
								}
							}
						}
					}
				}
			}

			if (obj && objNextName.length<=0)
			{
				FocusHandler.getInstance().setFocus(obj);
			}*/
		}

		public function UCSetFreeTips(elemName1:String,elemName2:String,elemName3:String,elemName4:String,Tips:String,Type:String):void
		{//主动设置某个元件的tips通用接口
			var obj;
			var objNextName:String;
			var obj1 = getChildByName(elemName1);
			if (obj1)
			{
				obj = obj1;
				objNextName = elemName2;
				if (elemName2.length > 0)
				{
					var obj2 = obj1.getChildByName(elemName2);
					if (obj2)
					{
						obj = obj2;
						objNextName = elemName3;
						if (elemName3.length > 0)
						{
							var obj3 = obj2.getChildByName(elemName3);
							if (obj3)
							{
								obj = obj3;
								objNextName = elemName4;
								if (elemName4.length > 0)
								{
									var obj4 = obj3.getChildByName(elemName4);
									if (obj4)
									{
										obj = obj4;
										objNextName = "";
									}
								}
							}
						}
					}
				}
			}

			if (obj && objNextName.length<=0)
			{
				obj.FreeTipsObj = {tipsString:Tips,tipsType:Type};
				obj.addEventListener( MouseEvent.ROLL_OVER,handleMouseRollOver );
				obj.addEventListener( MouseEvent.ROLL_OUT,handleMouseRollOut );
			}

		}

		public function handleMouseRollOver(event:MouseEvent):void
		{
			//trace(event.currentTarget.handleMouseRollOver);
			if (event.currentTarget.handleMouseRollOver != null)
			{
				event.currentTarget.handleMouseRollOver(event);
			}
			if (event.currentTarget.FreeTipsObj)
			{
				ExternalInterface.call("ASShowFreeTips", event.currentTarget,true);
			}
		}

		public function handleMouseRollOut(event:MouseEvent):void
		{
			if (event.currentTarget.handleMouseRollOut != null)
			{
				event.currentTarget.handleMouseRollOut(event);
			}
			if (event.currentTarget.FreeTipsObj)
			{
				ExternalInterface.call("ASShowFreeTips", event.currentTarget,false);
			}
		}

		/**
		* Show or hide the component. Allows the {@code _visible} property to be overridden, and 
		* dispatch a "show" or "hide" event.
		* add by JimZhang@snda.com
		*/
/*		[Inspectable(defaultValue = "true")]
		override public function get visible():Boolean
		{
			return super.visible;
		}
		override public function set visible(value:Boolean):void
		{
			if (value)
			{
				if (TweenShowFlag)
				{
					TweenShow = new Tween(1000,this,{scaleX:1,scaleY:1,alpha:1},{paused:true,ease:Strong.easeOut,onComplete:onTweenComplete,loop:false});
					if (TweenShow)
					{
						scaleX = 1;
						scaleY = 1;
						alpha = 0;
						TweenShow.reset();
						TweenShow.paused = false;
					}
				}
			}else{
				setCenter();//还原窗口位置为居中状态
			}
			super.visible = value;
		}*/

/*		private function onTweenComplete():void
		{
			if (TweenShow)
			{
				TweenShow.paused = true;
			}
			alpha = 1;
		}*/

		public function GrayChildMc( mc:MovieClip, gray:Boolean )
		{
			if (! mc)
			{
				return;
			}
			if (gray)
			{
				mc.filters = [ StyleType.getInstance().getBlackFilter() ];
			}
			else
			{
				mc.filters = null;
			}
		}
		
		public function UCGetWidth():int
		{
			if(MyWindowsFrame_mc){
				return MyWindowsFrame_mc.width;//fix new window use mask in background 
			}
			return this.OrignW;
		}

		public function UCGetHeight():int
		{
			return this.OrignH;
		}
		
		public function UCGetOptimizationWidth():int
		{
			//return this.width;
			return this.OrignW;
		}

		public function UCGetOptimizationHeight():int
		{
			//return this.height;
			return this.OrignH;
		}		

		public function getSlotByName(slotName:String):MyItemSlot
		{
			return null;
		}

		public function updateSlotData(slotDataArray:Array):void
		{
			var i:int;
			for (i = 0; i < slotDataArray.length; i++)
			{
				var slotData:Object = slotDataArray[i] as Object;
				var slot:MyItemSlot = getSlotByName(slotData.slotName);
				if (slot!=null)
				{
					slot.SetDataObj(slotData);
				}
			}
		}

		//add by JimZhang@sdna.com
		private function SetPanelDrag():void
		{
			if (InfoDragButton_mc != null)
			{
			    this.mouseEnabled = true;
			    InfoDragButton_mc.removeEventListener( MouseEvent.MOUSE_DOWN ,onWindowStartDrag,false);
			    InfoDragButton_mc.addEventListener( MouseEvent.MOUSE_DOWN ,onWindowStartDrag );
			}
		}

		public function OnFocusGained():void
		{//焦点获得--目前不在使用此接口
			//ExternalInterface.call( "ASTrace", "OnFocusGained MyPanel" );
		}

		public function OnFocusLost()
		{//焦点失去--目前不在使用此接口
/*			if(root.stage){
				FocusHandler.getInstance().setFocus(this);
			    bDrag = false;
			}*/
		}
		public function CanFocusLost():Boolean
		{
			return !bDrag;
		}

        protected function onWindowStartDrag(e:Event):void {
		   onWindowSwapToFront(null);
           root.stage.addEventListener(MouseEvent.MOUSE_UP, onWindowStopDrag, false, 0, true);
           startDrag();
		   bDrag = true;
        }
        
        protected function onWindowStopDrag(e:Event):void {
            root.stage.removeEventListener(MouseEvent.MOUSE_UP, onWindowStopDrag, false);
            stopDrag();
			bDrag = false;
        }
		
		/**
		 * 设置为居中 
		 * 
		 */		
		public function setCenter():void
		{
			if(MyWindowsFrame_mc != null && ShowMode == "BC")
			{
				this.x = (cavasWidth - MyWindowsFrame_mc.width) >> 1;
			    this.y = (cavasHeight - MyWindowsFrame_mc.height) >> 1;
			}
		}

		public function UpdatePos( stageW:Number , stageH:Number )
		{
			setCenter();
		}
		
		public function UCShowMode():void
		{
			scaleform.clik.managers.PopUpManager.showModal(this);
			dispatchEvent(new ComponentEvent(ComponentEvent.SHOW));
		}
		
		public function UCDismissMode():void
		{
			scaleform.clik.managers.PopUpManager.showModal(null);
		}
		
		public function UCShow(v:Boolean, priority:int):void
		{
			trace("+++++++++++++++++ MyPanel::UCShow:", v, " priority:", priority, this);			
			if(v)
			{
				_displayPriority = priority;
				PopUpManager.show(this, -1, -1, null, priority);
				dispatchEvent(new ComponentEvent(ComponentEvent.SHOW));
			}
			else
			{
				setCenter();//还原窗口位置为居中状态
				if(this.parent)
				{
					this.parent.removeChild(this);
				}
				dispatchEvent(new ComponentEvent(ComponentEvent.HIDE));
			}
		}

	}
}