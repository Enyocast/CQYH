package ActionScript3.fla
{
	import ActionScript3.Tips.MyTooltips;
	import ActionScript3.Widget.BuffPanel;
	import ActionScript3.Widget.FBSummaryProgressBar;
	import ActionScript3.Widget.HintLevelUpWidget;
	import ActionScript3.Widget.HintSceneWidget;
	import ActionScript3.Widget.ProgressBarQTEWidget;
	import ActionScript3.Widget.ProgressBarStrengthWidget;
	import ActionScript3.Widget.ProgressBarWidget;
	import ActionScript3.Widget.ProgressBloodBar;

	import UI_DynamicUIWidget.AS3.RenownUnlockAOG;
	
	import scaleform.clik.controls.UILoader;
	import flash.external.ExternalInterface;
    import flash.events.Event;
	import flash.events.ProgressEvent;
	import flash.display.MovieClip;
	import flash.utils.Dictionary;
	import ActionScript3.MyPanel;
	import flash.display.Loader;
	import flash.display.Bitmap;
	import flash.display.DisplayObject;
	import UI_DynamicUIWidget.AS3.TransducerWidget;
	import UI_DynamicUIWidget.AS3.HintGetItemWidget;
	import UI_DynamicUIWidget.AS3.BattleStats;
	import UI_DynamicUIWidget.AS3.WeatherChangePanel;
	import UI_DynamicUIWidget.AS3.NewEventPanel;
	
	public class MoviePlayer_DynamicUI extends MoviePlayerBase
	{
       
		public var 	_Tips:MyTooltips;
		public var	_BattleState:BattleStats;
		public var _FBSummaryProgressBar:FBSummaryProgressBar;
		public var _ProgressBar:ProgressBarWidget;
		public var _Scene:HintSceneWidget;
		public var _LevelUp:HintLevelUpWidget;
		public var _StrengthBar:ProgressBarStrengthWidget;
		public var _QTEBar:ProgressBarQTEWidget;
		public var _BossBlood:ProgressBloodBar;
		public var _UnlockAOGString:RenownUnlockAOG;
		public var _WeatherChange:WeatherChangePanel;
		public var _TransducerInfo:TransducerWidget;
		public var _NewEvent:NewEventPanel;
		public var BuffPanel_mc:BuffPanel;
		public var DropIcon_mc:DropIcon;
		public var hintGetItem_mc:HintGetItemWidget
		//public var AbilityCastbarStrength_mc:ProgressBarStrengthWidget;
		public var rootContainer:MovieClip;
		public var dic:Dictionary;
		override protected function configUI():void
		{
			super.configUI();
			dic=new Dictionary();
			DropIcon_mc.visible = false;
			//tips_item.tips_item_text.height = 50;
			//tips_item.tips_item_text.wordWrap = true;
			//tips_item.tips_item_text.autoSize = "left";
			//tips_item.tips_item_text.text = "东方不败冲寒江湖\ndd\nd\nd\nd\nd\nd\nd\nd\nd\nover";
			//tips_item.height = 100;
			//tips_item.TipsBg.height = 100;
			
		
			//BattleStats_mc.gotoAndPlay(2);
			//BattleStats_mc.textField.text = "333";
			
			//ScreenPopUpBoxMsgAOGMc.UCSetMsgInfo( 1, "获得技能", "牛逼技能", "0.TGA", "");
			//ScreenPopUpBoxMsgAOGMc.UCSetMsgInfo( 2, "您已获得了", "主动技能槽解锁", "", "1键");
			//ScreenPopUpBoxMsgAOGMc.UCSetMsgInfo( 3, "多重箭", "等级升到2级", "0.TGA", "");
			//HintScene.ShowHintScene( "比奇省复活点激活",24);
			
			//UCLoadMovie("../UI_CharactorWidget/CharactorWidget.swf");
			//UCLoadMovie("../UI_BagWidget/BagWidget.swf");
			//UCLoadMovie("../UI_WorldMap/WorldMap.swf");
			//UCLoadMovie("../UI_Journey/Journey.swf");
		}
		
		
		
		public function UCLoadMovie(swfURL:String):void
		{
			//ExternalInterface.call( "ASTrace", "############## loadMovie:" + swfURL);
			var swfLoader:UILoader = new UILoader();
			swfLoader.enableInitCallback = true;
			swfLoader.source = swfURL;
			swfLoader.maintainAspectRatio=false;
			dic[swfURL]=swfLoader;
			//swfLoader.addEventListener(Event.COMPLETE,handleLoadComplete,false,0,true);
			//swfLoader.loader.addEventListener(Event.OPEN, handleLoadIOError, false, 0, true);
			//swfLoader.loader.addEventListener(Event.OPEN, handleLoadOpen, false, 0, true);
			//swfLoader.loader.addEventListener(Event.OPEN, handleLoadInit, false, 0, true);
			//swfLoader.loader.addEventListener(Event.OPEN, handleLoadProgress, false, 0, true);
			this.stage.addChild(swfLoader);
			
		}
		
		public function UCUnLoadMovie(dat:String):void
		{
			if( dic[dat]){
				var swfLoader:UILoader = dic[dat];
				swfLoader.source="";
				this.stage.removeChild(swfLoader);
				swfLoader=null;
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
			var loader:Loader=Loader(e.target.loader);
			trace("############## handleLoadComplete",(loader.content as DisplayObject).width,(loader.content as DisplayObject).height)
            ExternalInterface.call( "ASTrace", "############## handleLoadComplete:" +  e.toString());
        }
	}
}