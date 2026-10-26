package UI_Root.AS3
{
	import flash.display.DisplayObject;
	import flash.display.Loader;
	import flash.display.MovieClip;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.ProgressEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.Dictionary;
	
	import ActionScript3.DropIcon;
	import ActionScript3.fla.MoviePlayerBase;
	
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.managers.PopUpManager;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.core.CLIK;
	import scaleform.clik.managers.FocusHandler;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextInput;

	public class MoviePlayer_Root extends MoviePlayerBase
	{
		//public var rootContainer:MovieClip;
		public var dic:Dictionary;
		//public var txt:TextField;
		public var DropIcon_mc:DropIcon;
		public var _subtiltle_mc:UIComponent;
		override protected function configUI():void
		{
			super.configUI();
			dic=new Dictionary();
			root.stage.scaleMode = StageScaleMode.NO_SCALE;
			root.stage.align = flash.display.StageAlign.TOP_LEFT;
			DropIcon_mc.mouseEnabled = false;
			DropIcon_mc.mouseChildren = false;

			PopUpManager.addToDragCanvas(DropIcon_mc);
			DropIcon_mc.visible = false;
			DropIcon_mc.parent.mouseChildren=false;
			DropIcon_mc.parent.mouseEnabled=false;
			//stage.addEventListener(MouseEvent.CLICK,handler);
			DropdownMenu;//reference of the class
			FocusHandler;
			UIComponent; 
			Button;
			TextInput;
			//UCLoadMovie("../UI_LoginWidget/LoginWidget.swf");
			//UCLoadMovie("../UI_CharactorWidget/CharactorWidget.swf");
			//UCLoadMovie("../UI_BagWidget/BagWidget.swf");
			//UCLoadMovie("../UI_OptionWidget/OptionWidget.swf");
			//UCLoadMovie("../UI_WorldMap/WorldMap.swf");
			//UCLoadMovie("../UI_ChatWidget/ChatWidget.swf");
			//for(var i:int = 0; i < this.numChildren; ++i)
			//{
			//	trace(" Root child:", this.getChildAt(i));
		//	}
		}
		
/*		private function handler(evt:MouseEvent):void
		{
			trace(evt.target.name);
		}*/
		
		public function getDropIcon():Object
		{
			return DropIcon_mc;
		}
		
		public function traceAllChild():void
		{
			for(var i:int = 0; i < this.numChildren; ++i)
			{
				trace("********** MoviePlayer_Root::Child", this.getChildAt(i));
			}
		}
		
		
		public function UCLoadMovie(swfURL:String):void
		{
			//ExternalInterface.call( "ASTrace", "############## loadMovie:" + swfURL);
			var swfLoader:UILoader = new UILoader();
			swfLoader.addEventListener(MouseEvent.CLICK,clickHandler);
			root.stage.addChild(swfLoader);
			swfLoader.enableInitCallback = true;
			swfLoader.source = swfURL;
			swfLoader.maintainAspectRatio=false;
			dic[swfURL]=swfLoader;
			//swfLoader.loader.addEventListener(Event.OPEN, handleLoadIOError, false, 0, true);
			//swfLoader.loader.addEventListener(Event.OPEN, handleLoadOpen, false, 0, true);
			//swfLoader.loader.addEventListener(Event.OPEN, handleLoadInit, false, 0, true);
			//swfLoader.loader.addEventListener(Event.OPEN, handleLoadProgress, false, 0, true);
			//swfLoader.addEventListener(Event.COMPLETE,handleLoadComplete,false,0,true);
		}
		
		private function clickHandler(evt:MouseEvent):void
		{
			var ld:UILoader=evt.currentTarget as UILoader;
			if(ld)
			{
				root.stage.setChildIndex(ld,root.stage.numChildren-1);
			}
		}
		
		public function UCUnLoadMovie(dat:String):void
		{
			if( dic[dat]){
				var swfLoader:UILoader = dic[dat];
				swfLoader.source="";
				root.stage.removeChild(swfLoader);
				swfLoader=null;
			}
		}
		
		public function UCClearFocus():void
		{
			if(CLIK.disableNullFocusMoves==true)
			{
				trace("CLIK.disableNullFocusMoves", CLIK.disableNullFocusMoves);
				ExternalInterface.call( "ASTrace", "CLIK.disableNullFocusMoves", CLIK.disableNullFocusMoves);
				CLIK.disableNullFocusMoves=false;
			}
			if(FocusHandler.getInstance().getFocus(0)!=null)
			{
				FocusHandler.getInstance().setFocus(null);
				
			}
		}
		
		public function UCUpdateSubtitle(str:String)
		{
			var mc:MovieClip = this.getChildByName("_subtiltle_mc") as MovieClip;
			var txt:TextField = mc.getChildByName("_subtitle_txt") as TextField;
			txt.htmlText = str;
			trace("UCUpdateSubtitle:", str);
		}
		
		public function UCShow(v:Boolean, scrW:int, scrH:int)
		{
			var mc:MovieClip = this.getChildByName("_subtiltle_mc") as MovieClip;
			mc.visible = v;
			
			if(v)
			{
				var newX:int = (scrW - mc.width) / 2;
				var newY:int = (scrH - mc.height);
				mc.x = newX;
				mc.y = newY;
			}
		}

		 /** @private */
        protected function handleLoadIOError( ioe:Event ):void 
		{
            ExternalInterface.call( "ASTrace", "############## handleLoadIOError:" +  ioe.toString());
        }
        
        /** @private */
        protected function handleLoadOpen( e:Event ):void
		{
            ExternalInterface.call( "ASTrace", "############## handleLoadIOError:" +  e.toString());
        }
        
        /** @private */
        protected function handleLoadInit( e:Event ):void
		{
            ExternalInterface.call( "ASTrace", "############## handleLoadInit:" +  e.toString());
        }
        
        /** @private */
        protected function handleLoadProgress( pe:ProgressEvent ):void 
		{
            ExternalInterface.call( "ASTrace", "############## handleLoadProgress:" +  pe.toString());
        }
        
        /** @private */
        protected function handleLoadComplete( e:Event ):void
		{
			trace(e.target.width,e.target.height);
 			var loader:Loader=Loader(e.target.loader);
            ExternalInterface.call( "ASTrace", "############## handleLoadComplete:",(loader.content as DisplayObject).width,(loader.content as DisplayObject).height);
        }
	}
}